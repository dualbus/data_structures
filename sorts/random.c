/* 
 * KISS random number generator from:
 * <http://www0.cs.ucl.ac.uk/staff/d.jones/GoodPracticeRNG.pdf>
 */

/* Seed variables */ 
static unsigned int x = 123456789, y = 362436000, z = 521288629, c = 7654321;

unsigned int
rng() 
{ 
    unsigned long long t, a = 698769069ULL; 
    
    x = 69069*x+12345; 
    y ^= (y<<13); y ^= (y>>17); y ^= (y<<5); /* y must never be set to zero! */ 
    t = a*z+c; c = (t>>32); /* Also avoid setting z=c=0! */ 
       
    return x+y+(z=t); 
} 

void
rng_seed(unsigned int sx, unsigned int sy, unsigned int sz)
{
  x = sx;
  y = sy;
  z = sz;
}
