import re
import os
import sys

#----------------------------------------------------------------------------------------------------------------------

INFO_RE     = re.compile('info face="(?<face>.+?)"')
COMMON_RE   = re.compile('common lineHeight=(?<lineHeight>\d+) base=(?<base>\d+) scaleW=(?<width>\d+) scaleH=(?<height>\d+) ')
GLYPHS_RE   = re.compile('chars count=(?<count>\d+)')
GLYPH_RE    = re.compile('char id=(?<id>\d+)\s+x=(?<x>\d+)\s+y=(?<y>\d+)\s+width=(?<width>\d+)\s+height=(?<height>\d+)\s+xoffset=(?<xoffset>-?\d+)\s+yoffset=(?<yoffset>-?\d+)\s+xadvance=(?<xadvance>\d+)\s+')
KERNINGS_RE = re.compile('kernings count=(?<count>\d+)')
KERNING_RE  = re.compile('kerning first=(?<first>\d+)\s+second=(?<second>\d+)\s+amount=(?<amount>-?\d+)')

COMMON_REP_RE = re.compile(': Font(${lineHeight}, ${base}, ${width}, ${height}, ${pages}) {')
GLYPH_REP_RE  = re.compile('glyphs_[${id}] = new Glyph(${x}, ${y}, ${width}, ${height}, ${xoffset}, ${yoffset}, ${xadvance}, ${page});')
GLYPH_REP_RE  = re.compile('kernings_[${first}][${second}] = ${amount};')

#//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

def main():
    if len(sys.argv) != 3 or not sys.argv[1] or not sys.argv[2]:
        print '2 arguments needed - input .fnt and output .h'
        return
    
    file_in = open(sys.argv[1]).read()
    file_out = open(sys.argv[2], 'w')
    
    # line 1 - 'info'
    font_name = INFO_RE.search(file_in).group('face')
    
    # line 2 - 'common'
    m = COMMON_RE.search(file_in)
    lineHeight  = int(m.group('lineHeight'))
    base        = int(m.group('base'))
    width       = int(m.group('width'))
    height      = int(m.group('height'))

    # 'char's and 'kerning's
    glyphs = {}
    kernings = {}
    kernings_found = 0
    for line in file_in.split('\n'):
        
        m = GLYPHS_RE.search(line)
        if m:
            glyph_count = int(m.group('count'))
        
        m = GLYPH_RE.search(line)
        if m:
            glyphs[int(m.group('id'))] = {
                'x': int(m.group('x')),
                'y': int(m.group('y')),
                'width': int(m.group('width')),
                'height': int(m.group('height')),
                'xoffset': int(m.group('xoffset')),
                'yoffset': int(m.group('yoffset')),
                'xadvance': int(m.group('xadvance')) }
        
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
    
    pass
    
#//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

main()