attribute vec4 a_posL;
varying vec2 v_uv;
uniform mat4 u_wvp;

void main()
{
gl_Position =u_wvp*vec4(a_posL.xy,0.0,1.0);
v_uv=a_posL.zw;
}
//u_mvp*
   