in vec2 vUv;
out vec4 fragColor;

uniform vec3      iResolution;           // viewport resolution (in pixels)
uniform float     iTime;                 // shader playback time (in seconds)
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click

#define PI 3.1415926538
void main()
{
    vec2 fragCoord = vUv * iResolution.xy;
    vec4 col = vec4(0.,0.,0.,0.);
    vec2 posFromMouse = fragCoord - iMouse.xy;
    float d = length(posFromMouse);
    float angle = atan(posFromMouse.y, posFromMouse.x);
    
    
    float r = (30.0 + .8*sin(angle*8.0 + 8.0*iTime) + sin(1.0*(angle + iTime)));
    float R = d-r; //makes anitaliasing easier
    if (R > 0.f){
        col = vec4( .5 + .5*R/fwidth(R) );
    }
    
    fragColor = vec4(col);
}