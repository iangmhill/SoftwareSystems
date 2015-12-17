/*
C code sample for Ian Hill for Software Systems at Olin College
Implementation of a Circular Buffer
Copyright 2015 Ian Hill
*/

#include <stdlib.h>
#include <stdio.h>

#define LOG 1

typedef struct {
  float* buffer;
  int length;
  int head;
  int tail;
  int count;
} CircularBuffer;

/*
Initialize and allocate memory for a new CircularBuffer
*/
CircularBuffer* CircularBuffer_create(int length) {
  CircularBuffer* buffer = malloc(sizeof(CircularBuffer));
  buffer->length = length;
  buffer->head = 0;
  buffer->tail = 0;
  buffer->count = 0;
  buffer->buffer = malloc(length * sizeof(float));
  return buffer;
}

/*
Free the memory for an existing CircularBuffer
*/
void CircularBuffer_delete(CircularBuffer* buffer) {
  if (buffer == NULL) return;
  free(buffer->buffer);
  free(buffer);
}

/*
Add a float value to the CircularBuffer if space is available
*/
int CircularBuffer_push(CircularBuffer* buffer, float val) {
  if (buffer->count == buffer->length) {
    if (LOG) printf("PUSH FAILED - BUFFER FULL\n");
    return -1;
  } else {
    if (LOG) printf("PUSHED %f\n", val);
    buffer->buffer[buffer->head] = val;
    buffer->head = CircularBuffer_incr(buffer->head, buffer->length);
    buffer->count++;
    return 0;
  }
}

/*
Remove a float value from the CircularBuffer unless the buffer is empty
*/
int CircularBuffer_pop(CircularBuffer* buffer, float* val) {
  if (buffer->count == 0) {
    if (LOG) printf("POP FAILED - BUFFER EMPTY\n");
    return -1;
  } else {
    if (LOG) printf("POPPED %f\n", buffer->buffer[buffer->tail]);
    *val = buffer->buffer[buffer->tail];
    buffer->tail = CircularBuffer_incr(buffer->tail, buffer->length);
    buffer->count--;
    return 0;
  }
}

/*
Increment the value of a CircularBuffer index such that the buffer is circular
*/
int CircularBuffer_incr(int val, int length) {
  return (val + 1) % length;
}

/*
Print the complete state of a CircularBuffer
*/
void CircularBuffer_print(CircularBuffer* buffer) {
  printf("LENGTH: %i COUNT: %i HEAD: %i TAIL: %i\n",
      buffer->length, buffer->count, buffer->head, buffer->tail);
  int i;
  for (i = 0; i < buffer->length; i++) {
    printf("%f ", buffer->buffer[i]);
  }
  printf("\n\n");
}

int main(){
  CircularBuffer* buffer = CircularBuffer_create(5);
  CircularBuffer_print(buffer);
  CircularBuffer_push(buffer, 1);
  CircularBuffer_print(buffer);
  CircularBuffer_push(buffer, 2);
  CircularBuffer_print(buffer);
  CircularBuffer_push(buffer, 3);
  CircularBuffer_print(buffer);
  CircularBuffer_push(buffer, 4);
  CircularBuffer_print(buffer);
  CircularBuffer_push(buffer, 5);
  CircularBuffer_print(buffer);
  CircularBuffer_push(buffer, 7);
  CircularBuffer_print(buffer);
  float f;
  CircularBuffer_pop(buffer, &f);
  CircularBuffer_print(buffer);
  CircularBuffer_push(buffer, 7);
  CircularBuffer_print(buffer);
  CircularBuffer_pop(buffer, &f);
  CircularBuffer_print(buffer);
  CircularBuffer_pop(buffer, &f);
  CircularBuffer_print(buffer);
  CircularBuffer_pop(buffer, &f);
  CircularBuffer_print(buffer);
  CircularBuffer_pop(buffer, &f);
  CircularBuffer_print(buffer);
  CircularBuffer_pop(buffer, &f);
  CircularBuffer_print(buffer);
  CircularBuffer_pop(buffer, &f);
  CircularBuffer_print(buffer);
  return 0;
}