//
// Created by drosaca on 18/11/22.
//

#ifndef TOTIFF_ERROR_H
#define TOTIFF_ERROR_H

#include <iostream>
#include <utility>


class Error : public std::exception {
private:
    std::string message;

public:
   // explicit Error(char * msg) : message(msg) {}
    const char *what ()  const noexcept override{
        return const_cast<char *>(message.c_str());
    }
    Error() = delete;
    explicit Error(std::string msg) : message(std::move(msg)){


   }

};


#endif //TOTIFF_ERROR_H
