precision mediump float;                             
	                    
uniform sampler2D u_texture;
 
varying vec4 v_Color;                            
                       
void main()                                          
{                                                    
	vec4 texColor = texture2D(u_texture, gl_PointCoord); 
	gl_FragColor = texColor * v_Color;     
}        