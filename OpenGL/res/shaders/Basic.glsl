#shader vertex
#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
out vec4 v_Color;

uniform mat4 u_TransformMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

void main()
{
   gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_TransformMatrix * position;
   v_TexCoord = texCoord;   
};

#shader fragment
#version 410 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
   vec4 texColor;
   texColor = texture(u_Texture, v_TexCoord);
   vec4 difuse = texColor * (u_Color * 2.5);
   if(false){
      difuse = texColor;
   }
   color = difuse;
};