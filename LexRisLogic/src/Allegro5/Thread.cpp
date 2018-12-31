/* Thread.cpp -- Thread Allegro 5 Source - LexRis Logic Headers

    Copyright (c) 2017-2019 LexRisLogic

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
    documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
    rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so.

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of
    the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "../../include/LexRisLogic/Allegro5/Thread.h"

namespace LL_AL5
{
    void* LL_SHARED __thread_main_function__(ALLEGRO_THREAD* thread,void* data)
    {
        if(data)
        {
            Thread* real_thread=(Thread*)data;
            if(real_thread->_P_Function_thread)
                return real_thread->_P_Function_thread(real_thread->_V_argv);
        }
        return nullptr;
    }

    Thread::Thread()
    {
    }
    bool Thread::set_function(void* (*new_function)(void*))
    {
        if(_V_thread)
            return false;
        _P_Function_thread=new_function;
        return true;
    }
    void* (*Thread::get_function())(void*)
    {
        return _P_Function_thread;
    }
    bool Thread::set_argv(void* new_argv)
    {
        if(_V_thread)
            return false;
        _V_argv=new_argv;
        return true;
    }
    void* Thread::get_argv()
    {
        return _V_argv;
    }
    bool Thread::start()
    {
        if(!_V_thread && _P_Function_thread)
        {
            _V_thread=al_create_thread(__thread_main_function__,this);
            if(_V_thread)
            {
                al_start_thread(_V_thread);
                return true;
            }
        }
        return false;
    }
    void* Thread::join()
    {
        if(_V_thread)
        {
            void* output=nullptr;
            al_join_thread(_V_thread,&output);
            return output;
        }
        return nullptr;
    }
    bool Thread::destroy()
    {
        if(_V_thread)
        {
            al_destroy_thread(_V_thread);
            _V_thread=nullptr;
            return true;
        }
        return false;
    }
    Thread::operator ALLEGRO_THREAD* ()
    {
        return _V_thread;
    }
    Thread::~Thread()
    {
        destroy();
    }
}
