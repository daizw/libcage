/*
 * Copyright (c) 2009, Yuuki Takano (ytakanoster@gmail.com).
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the writers nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DHT_HPP
#define DHT_HPP

#include "common.hpp"

#include "bn.hpp"
#include "dtun.hpp"
#include "timer.hpp"
#include "peers.hpp"
#include "rttable.hpp"
#include "udphandler.hpp"

namespace libcage {
        class dht : public rttable {
        public:
                dht(const uint160_t &id, timer &t, peers &p, udphandler &udp,
                    dtun &dt);
                virtual ~dht();

                void            recv_ping(void *msg, sockaddr *from,
                                          int fromlen);
                void            recv_ping_reply(void *msg, sockaddr *from,
                                                int fromlen);

        private:
                virtual void    send_ping(cageaddr &dst, uint32_t nonce);

                class ping_func {
                public:
                        void operator() (bool result, cageaddr &addr);

                        cageaddr        dst;
                        uint32_t        nonce;
                        dht            *p_dht;
                };

                const uint160_t         &m_id;
                timer          &m_timer;
                peers          &m_peers;
                udphandler     &m_udp;
                dtun           &m_dtun;
        };
}

#endif // DHT_HPP