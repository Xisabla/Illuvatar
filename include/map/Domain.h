/*=========================================================================

  Project:   Illuvatar
  File:      Domain.h

  Copyright (c) 2021 - All rights reserved
  Distributed under the MIT License (https://opensource.org/licenses/MIT)

=========================================================================*/
#pragma once
#ifndef ILLUVATAR_DOMAIN_H
#define ILLUVATAR_DOMAIN_H

/**
 * @class Domain
 * @brief Geometrical domain in which the map exists, act as "borders" of the map.
 *  Used to generate and plot the map.
 */
class Domain {
  public:
    Domain(unsigned int width, unsigned int height);

    // - Getters -----------------------------------------------------------------------------
    [[nodiscard]] unsigned int width() const;
    [[nodiscard]] unsigned int height() const;

  private:
    // - Attributes --------------------------------------------------------------------------
    unsigned int _width;
    unsigned int _height;
};


#endif // ILLUVATAR_DOMAIN_H
