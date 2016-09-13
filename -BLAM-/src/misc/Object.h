/* Object.h
 *
 * The interface for the Object subclass, which contains most of the dynamic
 * objects used in the system.  Implements a simple, manual reference-count
 * system.
 *
 * Author: David Riley
 */

#ifndef OBJECT_H
#define OBJECT_H


class Object
{
  public:
   /* Object()
    *
    * Creates the object with an initial reference count of 1.
    */
   Object(void);

   /* We need to make the destructor virtual. */
   virtual ~Object(void);

   /* retain()
    *
    * Adds one to the reference count.
    *
    * Parameters: None.
    * Returns: None.
    */
   void retain(void);

   /* release()
    *
    * Decrements the reference count by one, releasing the object if the count
    * goes to 0.
    */
   void release(void);

  private:
   
   // Our reference count.  We don't specify a size, since any normal-sized int
   // really ought to do.
   unsigned int m_refcount;
};


#endif // OBJECT_H
