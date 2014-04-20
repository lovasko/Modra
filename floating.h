#ifdef TEST_DOUBLE
	#define MyFloating GLdouble
	#define MY_FLOATING GL_DOUBLE
	#define TypeName "double"
	#define myTexCoord2v glTexCoord2dv
	#define myColor4v glColor4dv
	#define myNormal3v glNormal3dv
	#define myVertex3v glVertex3dv
#endif

#ifdef TEST_FLOAT
	#define MyFloating GLfloat
	#define MY_FLOATING GL_FLOAT
	#define TypeName "float"
	#define myTexCoord2v glTexCoord2fv
	#define myColor4v glColor4fv
	#define myNormal3v glNormal3fv
	#define myVertex3v glVertex3fv
#endif

