// transformation matrices
uniform mat4 modelview;
uniform mat4 projection;

// vertex attributes
in vec3 VERT_POSITION;
in vec3 VERT_NORMAL;
in vec4 VERT_COLOR;
in vec2 VERT_TEX_COORD;

// lighting data
in vec4 LIGHT_DATA[6];

// material data
in vec4 MATERIAL_DATA[6];

// output vertex data
out VertexData {
    vec3 position;    
    vec3 normal;
    vec4 color;
    vec2 texCoord;
} VertexOut;

// output light data
out LightData {
    
    vec4 position, ambient, diffuse, specular;
    vec3 spotDirection;
    float spotExponent, spotCutoff;
    float constAttenuation, linearAttenuation, quadAttenuation;
} LightOut;

// output material data
out MaterialData {
    
    vec4 ambient, diffuse, specular, emission, ambAndDiff;
    vec3 colorIndices;
    float shininess;
} MaterialOut;

// shader program
void main(void) {
    
   VertexOut.position = VERT_POSITION;
   VertexOut.normal = VERT_NORMAL;
   VertexOut.color = VERT_COLOR;
   VertexOut.texCoord = VERT_TEX_COORD;
   
   LightOut.position = LIGHT_DATA[0];    
   LightOut.ambient = LIGHT_DATA[1];
   LightOut.diffuse = LIGHT_DATA[2];
   LightOut.specular = LIGHT_DATA[3];
   LightOut.spotDirection = LIGHT_DATA[4].xyz;    
   LightOut.spotExponent = LIGHT_DATA[4].w;
   LightOut.spotCutoff = LIGHT_DATA[5].x;
   LightOut.constAttenuation = LIGHT_DATA[5].y;
   LightOut.linearAttenuation = LIGHT_DATA[5].z;    
   LightOut.quadAttenuation = LIGHT_DATA[5].w;

   MaterialOut.ambient = MATERIAL_DATA[0];
   MaterialOut.diffuse = MATERIAL_DATA[1];
   MaterialOut.specular = MATERIAL_DATA[2];
   MaterialOut.emission = MATERIAL_DATA[3];
   MaterialOut.ambAndDiff = MATERIAL_DATA[4];
   MaterialOut.colorIndices = MATERIAL_DATA[5].xyz;
   MaterialOut.shininess = MATERIAL_DATA[5].w;
   
   // fix me -> might need to mult in a projection and modelview matrix (need uniforms to do this)
   gl_Position = /*modelview * projection * */vec4(VERT_POSITION, 1.0);
}
