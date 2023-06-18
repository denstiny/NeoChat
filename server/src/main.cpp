#include "server/server.hpp"
#include "tasks/tasks.hpp"
#include "ReConf/ReConf.hpp"

int main (int argc, char* argv[]) {
  ReConf re_conf;
  bool re_conf_status;
  ThreadPool pool;
  Server ser (&pool);
  int listen_fd;
  int epoll_fd;
  int oldfd_opt;
  epoll_event events[MAX_EVENTS_NUMBER];
  
  /* load server configuration file */
  re_conf_status = re_conf.Load (CONFIGPATH);
  if (!re_conf_status) {
    return -1;
  }
  // init thread pool
  pool.Init (re_conf.GetInt ("THREADPOLLNUM"));
  /* init server */
  listen_fd = ser.Init (re_conf.GetChar ("SERVERIP"),
                        re_conf.GetInt ("SERVERPORT"));
  // set server sock no block and use ET mode
  oldfd_opt = setnoblocking ( listen_fd);
  epoll_fd = epoll_create (re_conf.GetInt ("THREADPOLLNAME"));
  add_fd (epoll_fd, listen_fd);
  
  while (1) {
    // polling event poll tasks to thread pool
    int ret = epoll_wait (epoll_fd, events, MAX_EVENTS_NUMBER, -1);
    if (ret < 0 and errno != EINTR) {
      perror ("epoll wait"); break;
    }
    pool.Submit ([&ser, ret, epoll_fd, &listen_fd, &events]() {
      ser.EventWith (epoll_fd, ret, listen_fd, events);
    });
  }
  pool.shutdown();
  close (listen_fd);
  return 0;
}
