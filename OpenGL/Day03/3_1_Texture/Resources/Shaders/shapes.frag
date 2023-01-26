#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 texCoord;
uniform sampler2D textureWall;

void main(){
    //FragColor = vec4(1.0,0.5,0.2,1.0);
    //使用纹理进行贴图
    FragColor = texture2D(textureWall,texCoord);
}
