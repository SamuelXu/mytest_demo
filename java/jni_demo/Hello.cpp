
#include <stdio.h>
#include <string.h>
#include "Hello.h"

/*
 * Class:     Hello
 * Method:    intMethod
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_Hello_intMethod
  (JNIEnv *env, jobject jobj, jint jvar)
{
	return jvar * jvar;
}

/*
 * Class:     Hello
 * Method:    booleanMethod
 * Signature: (Z)Z
 */
JNIEXPORT jboolean JNICALL Java_Hello_booleanMethod
  (JNIEnv *env, jobject jobj, jboolean jvar)
{
	return !jvar;
}

static char* strupr(char* str)
{
	if( !str) return NULL;
	char* p = str;
	while( *p != '\0') {
		if( *p >= 'a' && *p <= 'z') {
			*p -= 32;
		}
		p++;
	}
	return str;
}

/*
 * Class:     Hello
 * Method:    stringMethod
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_Hello_stringMethod
  (JNIEnv *env, jobject jobj, jstring jstr)
{
	const char *str = env->GetStringUTFChars(jstr, 0);
	char cap[128];
	strcpy(cap, str);
	env->ReleaseStringUTFChars(jstr, str);
	return env->NewStringUTF(strupr(cap));
}

/*
 * Class:     Hello
 * Method:    intArrayMethod
 * Signature: ([I)I
 */
JNIEXPORT jint JNICALL Java_Hello_intArrayMethod
  (JNIEnv *env, jobject jobj, jintArray jarr)
{
	int i, sum = 0;
	jsize len = env->GetArrayLength(jarr);
	jint *body = env->GetIntArrayElements(jarr, 0);
	for (i=0; i<len; i++)
	{
		sum += body[i];
	}
	for (i=0; i<len/2; i++)
	{
		int a = body[i];
		body[i] = body[len-1-i];
		body[len-1-i] = a;
	}
	env->ReleaseIntArrayElements(jarr, body, 0);
	return sum;
}

/*
 * Class:     Hello
 * Method:    bytebufferMethod
 * Signature: (Ljava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_Hello_bytebufferMethod
  (JNIEnv *env, jobject jobj, jobject jbuf)
{
//	jclass cls = env->GetObjectClass(jbuf);
//	jmethodID mid = env->GetMethodID(cls, "limit", "(I)Ljava/nio/Buffer;");
	char *buf = (char*)env->GetDirectBufferAddress(jbuf);
	jlong capacity = env->GetDirectBufferCapacity(jbuf);
	if(capacity > 0) {
		printf("ByteBuffer inner:%ld %s\n", capacity, buf);
		buf[0]='I';
	} else {
		printf("XXXX ByteBuffer inner:%ld \n", capacity);
	}
}

/*
 * Class:     Hello
 * Method:    byteArrayMethod
 * Signature: ([B)V
 */
JNIEXPORT void JNICALL Java_Hello_byteArrayMethod
  (JNIEnv *env, jobject jobj, jbyteArray jarr)
{
	jsize len = env->GetArrayLength(jarr);
	jbyte* body = env->GetByteArrayElements(jarr, 0);
	if(len > 0) {
		printf("Byte[] inner:%ld %s\n", len, body);
	} else {
		printf("XXXXX Byte[] inner:%ld %s\n", len, body);
	}
	env->ReleaseByteArrayElements(jarr, body, 0);
}

