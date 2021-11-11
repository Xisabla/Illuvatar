/*=========================================================================

  Project:   Illuvatar
  File:      Singleton.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_SINGLETON_H
#define ILLUVATAR_SINGLETON_H

#include <memory>

// See: https://codereview.stackexchange.com/a/173942
// TL;DR: A static method is used to retrieve/create the instance. Methods to make a copy are set
// as "delete" to override default definitions. The protected "_token" structure is unreachable
// from outside the class or any child, it allows for a child class to overload the constructor
// while making it unable to use outside the scope of the class, so that the class still can't
// be constructed in any usual way.

/**
 * Singleton template implementation
 * @tparam T Singleton class
 */
template<typename T> class Singleton {
  public:
    /**
     * Retrieve or create the Singleton instance
     * @return The single instance of the class
     */
    static T& instance() {
        static const std::unique_ptr<T> instance { new T { _token {} } };
        return *instance;
    }

    // Forbidden methods
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton) = delete;

  protected:
    /**
     * @brief Public constructor guardian, allows constructor overloading
     */
    struct _token { };

    /**
     * @brief Default constructor
     */
    explicit Singleton(_token) {};
};

// Helpers
#define SINGLETON(name) class name final : public Singleton<name>

#endif // ILLUVATAR_SINGLETON_H
