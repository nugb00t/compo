
const Font::Glyph ${font_name}Font::GLYPH_DATA[] = {
${glyph_data}};

const Font::Glyph* const ${font_name}Font::GLYPHS[GLYPH_COUNT] = {
${glyph_index}};

const i8 ${font_name}Font::KERN_DATA[][KERN_MAP_COUNT] = {
${kern_data}};

const i8* const ${font_name}Font::KERNINGS[KERN_COUNT] = {
${kern_index}};

const Font::Info ${font_name}Font::INFO = {
${info}
};
