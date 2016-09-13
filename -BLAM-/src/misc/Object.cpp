/* Object.cpp
 *
 * Defines the methods for the Object base class, which implements a simple
 * manual reference count system to keep track of objects.
 *
 * Author: David Riley
 */

#include "util.h"

#include "Object.h"


/* Some special counting for debugging. */
#ifdef DEBUG
static int g_objcount = 0;
#endif

/* ctor
 *
 * Creates the object with an initial reference count of 1.
 */
Object::Object(void)
   : m_refcount(1)
{
    // Nothing special here unless we're debugging.
    vdprintf("Object %p created.\n", this);
    
    // We have to couch this in #ifdef DEBUG because otherwise the objcount
    // doesn't exist.
    #ifdef DEBUG
    vdprintf("Objects: %d\n", ++g_objcount);
    #endif
}

/* We need to make the destructor virtual. */
Object::~Object(void)
{
   vdprintf("Object %p destroyed.\n", this);
   if(m_refcount != 0)
       dprintf("*** Object %p: refcount not 0!\n", this);

   #ifdef DEBUG
   vdprintf("Objects: %d\n", --g_objcount);
   #endif
}

/* retain()
 *
 * Adds one to the reference count.
 *
 * Parameters: None.
 * Returns: None.
 */
void Object::retain(void)
{
   // Make sure we exist.
   if(this == NULL) return;
   
   // Increment the refcount like we're supposed to.
   m_refcount++;
   
   // Print debugging info if necessary.
   vdprintf("Object %p retained, refcount = %d.\n", this, m_refcount);
}

/* release()
 *
 * Decrements the reference count by one, releasing the object if the count
 * goes to 0.
 */
void Object::release(void)
{
   // Make sure we exist first.
   if(this == NULL) return;

   // Decrement the refcount like we're supposed to.
   m_refcount--;

   // Print debugging info.
   vdprintf("Object %p released, refcount = %d.\n", this, m_refcount);

   // Destroy the object if necessary.
   if(m_refcount == 0) delete this;
}

