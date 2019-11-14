#version 330 core

in vec3 m_normal;
in vec2 m_texCoord;

layout (location = 0) out vec4 color;

uniform sampler2D m_texture;
uniform vec4 m_color;


void main()
{
	color = texture2D(m_texture,vec2(m_texCoord.x, m_texCoord.y) );
		
	color.a = color.r;
	color.g = color.r;
	color.b = color.r;
	
	color *= m_color;
	
	//if(color.a <= 0)
	//	discard;
}