precision mediump float;

uniform sampler2D u_texture;
uniform float u_Time;

varying vec2 v_uv;
varying vec3 v_posL;

void main()
{
	gl_FragColor = texture2D(u_texture, v_uv);
}
