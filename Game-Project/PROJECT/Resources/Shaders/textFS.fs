precision mediump float;
varying vec2 v_uv;
uniform sampler2D u_texture;
uniform vec4 textColor;
void main()
{
	gl_FragColor = vec4(textColor.r, textColor.g, textColor.b,texture2D(u_texture, v_uv).a * textColor.a);
}