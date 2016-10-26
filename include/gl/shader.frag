// input vertex data
in VertexData {
    vec3 position;
    vec3 normal;
    vec4 color;
    vec2 texCoord;
} VertexIn;

// output color data
out vec4 ColorOut;
out vec4 NormalOut;

// shader program
void main() {

	ColorOut = VertexIn.color;
	NormalOut = vec4(VertexIn.normal, 0.0);
}
