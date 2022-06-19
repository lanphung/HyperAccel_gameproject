attribute vec3 a_posL;
attribute vec2 a_uv;

uniform mat4 u_wvp, u_w, u_v;

varying vec2 v_uv;
varying vec4 ViewDimension;

void main()
{
	vec4 posL = vec4(a_posL, 2.0);
	gl_Position = u_wvp * posL;
	ViewDimension = u_v * u_w * posL;
	v_uv = a_uv;
}

