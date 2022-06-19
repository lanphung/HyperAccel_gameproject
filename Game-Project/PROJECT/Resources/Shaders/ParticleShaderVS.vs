attribute vec4 a_pos;                       
attribute vec4 a_Color;        

varying	vec4 v_Color;

void main()                                          
{                                                   
	gl_Position = vec4(a_pos.xyz, 1.0);
	gl_PointSize = a_pos.w;
	v_Color = a_Color;
}