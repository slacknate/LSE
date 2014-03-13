// texture input
uniform sampler2D FRAG_TEXTURE;

// input vertex data
in VertexData {
    vec3 position;
    vec3 normal;
    vec4 color;
    vec2 texCoord;
} VertexIn;

// input vertex data
in LightData {
    
    vec4 position, ambient, diffuse, specular;
    vec3 spotDirection;
    float spotExponent, spotCutoff;
    float constAttenuation, linearAttenuation, quadAttenuation;
} LightIn;

// input vertex data
in MaterialData {
    
    vec4 ambient, diffuse, specular, emission, ambAndDiff;
    vec3 colorIndices;
    float shininess;
} MaterialIn;

// output color data
out vec4 ColorOut;

// shader program
void main(void) {
    
    vec3 lightVec = normalize(LightIn.position.xyz - VertexIn.position);
    vec4 diffuseLight = MaterialIn.diffuse * LightIn.diffuse * dot(VertexIn.normal, lightVec);
    
    ColorOut = vec4(0.0, 0.0, 0.0, 0.0) * diffuseLight;
}
