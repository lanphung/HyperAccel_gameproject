precision mediump float;

uniform sampler2D u_texture;


varying vec2 v_uv;


void main()
{
	gl_FragColor = texture2D(u_texture, v_uv);
        
        //gl_FragColor=vec4(1.0,1.0,1.0,1.0);
    gl_FragColor.a = 0.5;
}