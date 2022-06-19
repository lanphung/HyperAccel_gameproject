precision mediump float;
uniform sampler2D u_texture;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;
uniform vec3 camPos;

varying vec2 v_uv;
varying vec3 v_posL;
void main()
{
	vec4 tex0 = texture2D(u_texture, v_uv);
	vec4 tex1 = texture2D(u_texture1, v_uv);
	vec4 tex2 = texture2D(u_texture2, v_uv);
	vec4 tex3 = texture2D(u_texture3, v_uv);
	float DistCam = distance( camPos, v_posL);
	float Lerp = (DistCam - 101.0)/20.0;
	Lerp = clamp(Lerp, 0.0, 1.0);
	gl_FragColor = Lerp * vec4(1.0, 1.0, 1.0, 1.0)  + (1.0 - Lerp) * (tex3.r * tex0 + tex3.g * tex1 + tex3.b *tex2)/(tex3.r + tex3.g + tex3.b);
	//gl_FragColor = (tex3.r * tex0 + tex3.g * tex1 + tex3.b *tex2)/(tex3.r + tex3.g + tex3.b);
}
