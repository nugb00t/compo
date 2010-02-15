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

TEMPLATE_FONT_H         = 'tools/cook_font/template_font.h'
TEMPLATE_DATA_H         = 'tools/cook_font/template_data.h'
TEMPLATE_KERNED_FONT_H  = 'tools/cook_font/template_kerned_font.h'
TEMPLATE_KERNED_DATA_H  = 'tools/cook_font/template_kerned_data.h'

FOLDER_IN   = 'exec/fonts'
FOLDER_OUT  = 'engine/video/fonts'
 
#//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

def cook(file_in, dir_out):
	fnt_data_file = open(file_in)
	fnt_data = fnt_data_file.read()
	fnt_data_file.close()
	
	# line 1 - 'info'
	font_name = INFO_RE.search(fnt_data).group('face')
	font_name = '_'.join(font_name.split())
	class_name = '%sFont' % (font_name)
	
	# line 2 - 'common'
	m = COMMON_RE.search(fnt_data)
	info = {
		'lineHeight':	int(m.group('lineHeight')),
		'base':			int(m.group('base')),
		'width':		int(m.group('width')),
		'height':		int(m.group('height'))
	}

	# 'char's and 'kerning's
	print '  - parsing glyphs and kernings'
	glyphs = {}
	kernings = {}
	kerning_found = 0
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
			kerning_found = kerning_found + 1
			
			if int(m.group('first')) not in kernings:
				kernings[int(m.group('first'))] = {}
			
			kernings[int(m.group('first'))][int(m.group('second'))] = int(m.group('amount'))
	
	assert(len(glyphs) == glyph_count)
	if kerning_found:
		assert(kerning_found == kerning_count)
	
	font_h_path, min_kern_map, max_kern_map = generate_font_h(font_name, glyphs, kernings, dir_out)
	data_h_path = generate_data_h(font_name, info, glyphs, kernings, min_kern_map, max_kern_map, dir_out)
	
	return font_h_path, data_h_path

#//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

def generate_font_h(font_name, glyphs, kernings, dir_out):
	if len(kernings):
		template_file = open(TEMPLATE_KERNED_FONT_H)
	else:
		template_file = open(TEMPLATE_FONT_H)
	
	template = string.Template(template_file.read())
	template_file.close()
	
	# <>_font.h template mapping
	mapping = {
		'font_name_up':		font_name.upper(),
		'font_name':		font_name,
		'glyph_first':		str(min(glyphs.keys())),
		'glyph_count':		str(max(glyphs.keys()) - min(glyphs.keys()) + 1),
	}
	
	# kernings	
	print '  - processing kernings'
	if len(kernings):
		# kernings' mapped dimensions
		max_kern_map = min_kern_map = kernings[kernings.keys()[0]].keys()[0]
		for kern_id in kernings.keys():
			kerning = kernings[kern_id]
			min_kern_map = min(min_kern_map, min(kerning.keys()))
			max_kern_map = max(max_kern_map, max(kerning.keys()))
	 
		# extended <>_font.h template mapping
		mapping['kern_first']		= str(min(kernings.keys()))
		mapping['kern_count']		= str(max(kernings.keys()) - min(kernings.keys()) + 1)
		mapping['kern_map_first']	= str(min_kern_map)
		mapping['kern_map_count']	= str(max_kern_map - min_kern_map + 1)
	else:
		max_kern_map = min_kern_map = 0
	
	print '  - writing font header'
	file_path = os.path.join(dir_out, font_name.lower() + '_font.h')
	file = open(file_path, 'w')
	contents = template.substitute(mapping)
	file.write(contents)
	file.close()
	
	return file_path, min_kern_map, max_kern_map

#//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

def generate_data_h(font_name, info, glyphs, kernings, min_kern_map, max_kern_map, dir_out):
	if len(kernings):
		template_file = open(TEMPLATE_KERNED_DATA_H)
	else:
		template_file = open(TEMPLATE_DATA_H)
	
	template = string.Template(template_file.read())
	template_file.close()
	
	# glyph data
	print '  - generating glyph data'
	glyph_data = ''
	keys = glyphs.keys()
	keys.sort()
	for key in keys:
		glyph = glyphs[key]
		glyph_data += '\t{ { %ff, %ff, %ff, %ff }, { % d, % d, %d, %d }, %d, %d },\n' % (
			float(glyph['x']) / info['width'],						# u0
			float(glyph['y']) / info['height'],						# v0
			float(glyph['x'] + glyph['width']) / info['width'],		# u1
			float(glyph['y'] + glyph['height']) / info['height'],	# v1
			int(glyph['xoffset']),									# x0
			int(glyph['yoffset']),									# y0
			int(glyph['width']),									# width
			int(glyph['height']),									# height
			int(glyph['xadvance']),									# xAdvance
			int(0))													# page
	
	# glyph index
	print '  - generating glyph index'
	glyph_index = ''
	for key in range(min(glyphs.keys()), max(glyphs.keys()) + 1):
		if key in glyphs.keys():
			glyph_index += '\t&GLYPH_DATA[%d],\n' % (key - min(glyphs.keys()))
		else:
			glyph_index += '\tNULL,\n' 
	
	mapping = {
		'font_name':	font_name,
		'glyph_data':	glyph_data,
		'glyph_index':	glyph_index,
		'info':			'%s, %s, %s, %s' % (info['lineHeight'], info['base'], info['width'], info['height'])
	}
	
	if len(kernings):
		# kerning data
		print '  - generating kerning data'
		kern_data = ''
		keys = kernings.keys()
		keys.sort()
		for first in keys:
			kern_data += '\t{ '
			kerning = kernings[first]
			for second in range(min_kern_map, max_kern_map + 1):
				if second in kerning.keys():
					kern_data += '% 0d, ' % (kerning[second])
				else:
					kern_data += '0, '
			kern_data += ' },\n'
			
		mapping['kern_data']	= kern_data
		
		# kerning index
		print '  - generating kerning index'
		kern_index = ''
		for key in range(min(kernings.keys()), max(kernings.keys()) + 1):
			if key in kernings.keys():
				kern_index += '\tKERN_DATA[%d],\n' % (key - min(kernings.keys()))
			else:
				kern_index += '\tNULL,\n' 
		
		mapping['kern_index']	= kern_index

	print '  - writing font data'
	file_path = os.path.join(dir_out, font_name.lower() + '_font_data.h')
	file = open(file_path, 'w')
	contents = template.substitute(mapping)
	file.write(contents)
	file.close()
	
	return file_path

#//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

def main():
	for file_name in os.listdir(FOLDER_IN):
		if file_name.find('.fnt') == -1:
			continue
		file_path = os.path.join(FOLDER_IN, file_name)
		if (os.path.isfile(file_path)):
			print '\n+ processing ' + file_name
			cook(file_path, FOLDER_OUT)
        
#//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

main()