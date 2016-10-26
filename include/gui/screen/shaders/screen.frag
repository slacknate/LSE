// texture input
uniform sampler2D FRAG_TEXTURE;

// input vertex data
in VertexData {
    vec3 position;
    vec3 normal;
    vec4 color;
    vec2 texCoord;
} VertexIn;

// output color data
out vec4 ColorOut;

// shader program
void main() {

	ColorOut = texture(FRAG_TEXTURE, VertexIn.texCoord);
}
