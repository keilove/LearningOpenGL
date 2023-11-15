#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;

void main()
{	//我们使用GLSL内建的texture函数来采样纹理的颜色，
	//它第一个参数是纹理采样器，第二个参数是对应的纹理坐标。
	//texture函数会使用之前设置的纹理参数对相应的颜色值进行采样。
	//这个片段着色器的输出就是纹理的（插值）纹理坐标上的(过滤后的)颜色。
	FragColor = texture(texture1, TexCoord) ;
}
