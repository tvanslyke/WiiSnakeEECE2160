/*
 * EventReader.h
 *
 *  Created on: Apr 17, 2017
 *      Author: tim
 */

#ifndef EVENTREADER_H_
#define EVENTREADER_H_
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <functional>
#include <iostream>
class EventReader {
private:
	int fd;
protected:
	void * const buffer_;
	const size_t buffer_size_;
	void readEvent()
	{
		read(fd, buffer_, buffer_size_);
	}
public:
	EventReader(const char * event_file, void * const buffer_ptr, size_t bsize):
		buffer_(buffer_ptr),
		buffer_size_(bsize)

	{
		fd = open(event_file, O_RDONLY);
		if (fd == -1)
		{
			throw std::runtime_error((std::string("Error: Could not open event file (") + event_file + ")\nforgot sudo?\n").c_str());
		}
	}
	virtual ~EventReader()
	{
		close(fd);
	}
	virtual void setEventAction(int event_id, std::function<void(int)> &  action) = 0;
	virtual void checkEvent() = 0;
};

#endif /* EVENTREADER_H_ */
