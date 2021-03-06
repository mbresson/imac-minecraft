#version 330
 
layout(points) in;
layout(triangle_strip, max_vertices=32) out;
 
in vec4 pos[];
out vec2 tc;

//contient la matrice Model View Projection (elle sera envoyée par l'application au moment du dessin).
uniform mat4 uMVPMatrix = mat4(1.f) ;// la matrice de transformation sera l'identité par défaut
 
 void main()
{  
	for(int i = 0; i < gl_in.length(); i++)
	{
		//Face devant
		tc=vec2(1.0, 1.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(0.5,-0.5,0.5,0.0));
		EmitVertex();
		tc=vec2(1.0,0.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(0.5,0.5,0.5,0.0));
		EmitVertex();
		tc=vec2(0.0,1.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(-0.5,-0.5,0.5,0.0));
		EmitVertex();
		tc=vec2(0.0,0.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(-0.5,0.5,0.5,0.0));
		EmitVertex();
		EndPrimitive();
		
		//Face arriÃ¨re
		tc=vec2(0.0,1.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(0.5,-0.5,-0.5,0.0));
		EmitVertex();
		tc=vec2(0.0, 0.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(0.5,0.5,-0.5,0.0));
		EmitVertex();
		tc=vec2(1.0,1.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(-0.5,-0.5,-0.5,0.0));
		EmitVertex();
		tc=vec2(1.0,0.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(-0.5,0.5,-0.5,0.0));
		EmitVertex();
		EndPrimitive();
		
		//Face gauche
		tc=vec2(1.0,1.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(-0.5,-0.5,0.5,0.0));
		EmitVertex();
		tc=vec2(1.0, 0.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(-0.5,0.5,0.5,0.0));
		EmitVertex();
		tc=vec2(0.0,1.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(-0.5,-0.5,-0.5,0.0));
		EmitVertex();
		tc=vec2(0.0,0.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(-0.5,0.5,-0.5,0.0));
		EmitVertex();
		EndPrimitive();
		
		//Face droite
		tc=vec2(0.0,1.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(0.5,-0.5,0.5,0.0));
		EmitVertex();
		tc=vec2(0.0, 0.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(0.5,0.5,0.5,0.0));
		EmitVertex();
		tc=vec2(1.0,1.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(0.5,-0.5,-0.5,0.0));
		EmitVertex();
		tc=vec2(1.0,0.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(0.5,0.5,-0.5,0.0));
		EmitVertex();
		EndPrimitive();
		
		//Face dessus
		tc=vec2(1.0,0.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(0.5,0.5,-0.5,0.0));
		EmitVertex();
		tc=vec2(1.0, 1.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(0.5,0.5,0.5,0.0));
		EmitVertex();
		tc=vec2(0.0,0.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(-0.5,0.5,-0.5,0.0));
		EmitVertex();
		tc=vec2(0.0,1.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(-0.5,0.5,0.5,0.0));
		EmitVertex();
		EndPrimitive();
		
		//Face dessus
		tc=vec2(0.0,0.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(0.5,-0.5,-0.5,0.0));
		EmitVertex();
		tc=vec2(0.0, 1.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(0.5,-0.5,0.5,0.0));
		EmitVertex();
		tc=vec2(1.0,0.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(-0.5,-0.5,-0.5,0.0));
		EmitVertex();
		tc=vec2(1.0,1.0);
		gl_Position = uMVPMatrix*(pos[0].xyzw+vec4(-0.5,-0.5,0.5,0.0));
		EmitVertex();
		EndPrimitive();
	}	
}
