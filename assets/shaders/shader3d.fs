#version 330 core
out vec4 FragColor;
uniform vec3 color;   
uniform vec3 lightColor;

in vec2 TexCoord;
uniform sampler2D texture1;
uniform vec3 lightPos;  
in vec3 Normal;  
in vec3 FragPos; 
void main() {


    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 ambient = 0.1 * lightColor;
    vec3 result = ambient + diffuse;

    FragColor = vec4(color * result, 1.0);
    // FragColor = texture(texture1, TexCoord) * vec4(result, 1.0);

    
}
