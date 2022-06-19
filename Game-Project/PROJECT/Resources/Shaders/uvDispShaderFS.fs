precision mediump float;

uniform float u_Time;
uniform sampler2D u_texture; //fire texture
uniform sampler2D u_texture1; //fire mask
uniform sampler2D u_texture2; //uv disp

varying vec2 v_uv;
varying vec4 ViewDimension;
void main()
{
	vec2 disp = texture2D(u_texture2, vec2(v_uv.x, v_uv.y + u_Time)).rg;
	vec2 offset = (2.0 * disp - 1.0) * 0.05;
	vec2 Tex_coords_displaced = v_uv + offset;
	vec4 fire_color = texture2D(u_texture, Tex_coords_displaced);
	vec4 AlphaValue = texture2D(u_texture1, v_uv);
	float DistCam = abs(ViewDimension.z);
	float Lerp = (DistCam - 50.0)/20.0;
	Lerp = clamp(Lerp, 0.0, 1.0);
	gl_FragColor = Lerp * vec4(0.792, 0.466, 0.466, 0.0)  + (1.0 - Lerp) * fire_color * (1.0, 1.0, 1.0, AlphaValue.r);
}
