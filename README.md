# r2con2020-ctf-kernel

r2con2020-ctf-kernel exploit. 

Recently I found a challenge from [r2con](https://rada.re/con/2020/) at [Eloi Sanfelix's Github account](https://github.com/esanfelix/r2con2020-ctf-kernel). I gave it a try.

The vulnerability was `RESIZE` functionality doesn't lock `sock_buf_t` object while other functionalities sufficiently lock. This leads to a race condition between `RESIZE` and `SEND` functionalities. 

While window is really small, using `userfaultfd` blocks `copy_to/from_user` and provides us as much as time we need. 

Overwriting an existing `sock_buf_t` object enables us to gain arbitrary read/write. Sending buffer same size as `buf->size` increments  `write->index` to `buf->size` and it becomes 0 again, because of modulus operation. This primitive is helpful since we need to use read/write multiple times.


Based on solution of 2019 challenge: [Eloi Sanfelix r2con2019 Solution](https://github.com/esanfelix/r2con2019-ctf-kernel/tree/master/solution)

[@lntrx](https://twitter.com/lntrx)

References:

https://www.cons.org/cracauer/cracauer-userfaultfd.html

https://github.com/esanfelix/r2con2019-ctf-kernel
