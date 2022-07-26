#shader vertex
#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
out vec4 v_Color;

uniform mat4 u_MVP;

void main()
{
   gl_Position = u_MVP * position;
   v_TexCoord = texCoord;   
};

#shader fragment
#version 410 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform bool u_HasTexture;

void main()
{
   vec4 difuse = u_Color;
   if(u_HasTexture){
        difuse = texture(u_Texture, v_TexCoord) * (u_Color * 1.5);   
   }
   color = difuse;

 
};

