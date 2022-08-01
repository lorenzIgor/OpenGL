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
uniform bool u_HasTexture;

void main()
{
   vec4 difuse = u_Color;
   if(u_HasTexture){
        difuse = texture(u_Texture, v_TexCoord) * (u_Color * 1.5);   
   }

//   color = difuse;
//   color = vec4(1.0 - (gl_FragCoord.y / 1080), (gl_FragCoord.y / 1080), (gl_FragCoord.y / 1080), (gl_FragCoord.y / 1080) * 10) * 1.5;
   
//   vec2 u_resolution = vec2(1920.0,1080.0);
//   vec2 st = gl_FragCoord.xy/u_resolution;
//   
   gl_FragColor = vec4(1.0 - (gl_FragCoord.y / 1080), (gl_FragCoord.y / 1080), (gl_FragCoord.y / 1080), (gl_FragCoord.y / 1080) * 10) * 1.5;
 
};

