# HOWTO:
# 1. add project, browse for 'ipy.exe'
# 2. debugging options:
#	command:	 ${IRON_PYTHON}\ipy.exe
#	arguments:	 -D -i tools/cook_font.py exec/fonts/<font>.fnt

import re
import os
import string
import sys

#----------------------------------------------------------------------------------------------------------------------

INFO_RE	 = re.compile('info face="(?<face>.+?)"')
COMMON_RE   = re.compile('common lineHeight=(?<lineHeight>\d+) base=(?<base>\d+) scaleW=(?<width>\d+) scaleH=(?<height>\d+) ')

GLYPHS_RE   = re.compile('chars count=(?<count>\d+)')
GLYPH_RE	= re.compile('char id=(?<id>\d+)\s+x=(?<x>\d+)\s+y=(?<y>\d+)\s+width=(?<width>\d+)\s+height=(?<height>\d+)\s+xoffset=(?<xoffset>-?\d+)\s+yoffset=(?<yoffset>-?\d+)\s+xadvance=(?<xadvance>\d+)\s+')

KERNINGS_RE = re.compile('kernings count=(?<count>\d+)')
KERNING_RE  = re.compile('kerning first=(?<first>\d+)\s+second=(?<second>\d+)\s+amount=(?<amount>-?\d+)')

TEMPLATE_H		= 'tools/cook_font/template_font.h'
TEMPLATE_DATA_H	= 'tools/cook_font/template_font_data.h'

OUTPUT_PATH	= 'engine/video/fonts'

#//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

def main():
	if len(sys.argv) != 2 or not sys.argv[1]:
		print '2 arguments needed - input .fnt and output .h'
		return
	
	fnt_data_file = open(sys.argv[1])
	fnt_data = fnt_data_file.read()
	fnt_data_file.close()
	
	# line 1 - 'info'
	font_name = INFO_RE.search(fnt_data).group('face')
	class_name = '%sFont' % (font_name)
	
	# line 2 - 'common'
	m = COMMON_RE.search(fnt_data)
	lineHeight	= int(m.group('lineHeight'))
	base		= int(m.group('base'))
	width		= int(m.group('width'))
	height		= int(m.group('height'))

	# 'char's and 'kerning's
	glyphs = {}
	kernings = {}
	kernings_found = 0
	for line in fnt_data.split('\n'):
		
		m = GLYPHS_RE.search(line)
		if m:
			glyph_count = int(m.group('count'))
		
		m = GLYPH_RE.search(line)
		if m:
			glyphs[int(m.group('id'))] = {
				'x':		int(m.group('x')),
				'y':		int(m.group('y')),
				'width':	int(m.group('width')),
				'height':	int(m.group('height')),
				'xoffset':	int(m.group('xoffset')),
				'yoffset':	int(m.group('yoffset')),
				'xadvance':	int(m.group('xadvance')) }
		
		m = KERNINGS_RE.search(line)
		if m:
			kerning_count = int(m.group('count'))
		
		m = KERNING_RE.search(line)
		if m:
			kernings_found = kernings_found + 1
			
			if int(m.group('first')) not in kernings:
				kernings[int(m.group('first'))] = {}
			
			kernings[int(m.group('first'))][int(m.group('second'))] = int(m.group('amount'))
	
	assert(len(glyphs) == glyph_count)
	assert(kernings_found == kerning_count)
	
	# glyphs' mapped dimensions
	max_kern_map = min_kern_map = kernings[kernings.keys()[0]].keys()[0]
	for kern_id in kernings.keys():
		kerning = kernings[kern_id]
		min_kern_map = min(min_kern_map, min(kerning.keys()))
		max_kern_map = max(max_kern_map, max(kerning.keys()))
 
	# output .h
	template_h_file = open(TEMPLATE_H)
	template_h = string.Template(template_h_file.read())
	template_h_file.close()
	
	mapping_h = {
		'font_name_up':	font_name.upper(),
		'font_name':	font_name,
		'min_glyph':	str(min(glyphs.keys())),
		'max_glyph':	str(max(glyphs.keys())),
		'min_kern':		str(min(kernings.keys())),
		'max_kern':		str(max(kernings.keys())),
		'min_kern_map':	str(min_kern_map),
		'max_kern_map':	str(max_kern_map),
	}
	
	file_h = open(os.path.join(OUTPUT_PATH, font_name.lower() + '_font.h'), 'w')
	file_h.write(template_h.substitute(mapping_h))
	file_h.close()
	
	# output data.h
	template_data_h_file = open(TEMPLATE_DATA_H)
	template_data_h = string.Template(template_data_h_file.read())
	template_data_h_file.close()
	
	glyph_data = ''
	keys = glyphs.keys()
	keys.sort()
	for key in keys:
		glyph = glyphs[key]
		glyph_data += '\t{ %ff, %ff, %ff, %ff, %d, %d, %d, %d },\n' % (
			float(glyph['x']) / width,						# u0
			float(glyph['y']) / height,						# v0
			float(glyph['x'] + glyph['width']) / width,		# u1
			float(glyph['y'] + glyph['height']) / height,	# v1
			int(glyph['xoffset']),							# xOffset
			int(glyph['yoffset']),							# yOffset
			int(glyph['xadvance']),							# xAdvance
			int(0))											# page
	
	glyph_index = ''
	for key in range(min(glyphs.keys()), max(glyphs.keys()) + 1):
		if key in glyphs.keys():
			glyph_index += '\t&GLYPH_DATA[%d],\n' % (key)
		else:
			glyph_index += '\tNULL,\n' 
	
	kern_data = ''
	keys = kernings.keys()
	keys.sort()
	for first in keys:
		kern_data += '\t{ '
		kerning = kernings[first]
		for second in range(min_kern_map, max_kern_map + 1):
			if second in kerning.keys():
				kern_data += '%d, ' % (kerning[second])
			else:
				kern_data += '0, '
		kern_data += ' },\n'
	
	kern_index = ''
	for key in range(min(kernings.keys()), max(kernings.keys()) + 1):
		if key in kernings.keys():
			kern_index += '\tKERN_DATA[%d],\n' % (key)
		else:
			kern_index += '\tNULL,\n' 
	
	mapping_data_h = {
		'font_name':	font_name,
		'glyph_data':	glyph_data,
		'glyph_index':	glyph_index,
		'kern_data':	kern_data,
		'kern_index':	kern_index,
		'info':			'\t%s, %s, %s, %s' % (lineHeight, base, width, height)
	}

	file_data_h = open(os.path.join(OUTPUT_PATH, font_name.lower() + '_font_data.h'), 'w')
	file_data_h.write(template_data_h.substitute(mapping_data_h))
	file_data_h.close()

#//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

main()