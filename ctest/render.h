/*
 * pycsdl2
 * Copyright (c) 2015 Paul Tan <pyokagan@pyokagan.name>
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *     1. The origin of this software must not be misrepresented; you must
 *        not claim that you wrote the original software. If you use this
 *        software in a product, an acknowledgment in the product
 *        documentation would be appreciated but is not required.
 *     2. Altered source versions must be plainly marked as such, and must
 *        not be misrepresented as being the original software.
 *     3. This notice may not be removed or altered from any source
 *        distribution.
 */
/**
 * \file render.h
 * \brief Tests for csdl2's SDL_render bindings.
 */
#ifndef _PYCSDL2TEST_RENDER_H_
#define _PYCSDL2TEST_RENDER_H_
#include <Python.h>
#include <SDL_render.h>
#include "../include/pycsdl2.h"

/**
 * \brief Creates a PyCSDL2_RendererInfo object.
 *
 * \code{.py}
 * rendererinfo() -> SDL_RendererInfo
 * \endcode
 */
static PyObject *
PyCSDL2Test_RendererInfo(PyObject *module, PyObject *args)
{
    SDL_RendererInfo info = {
        /* name */ "name",
        /* flags */ 1,
        /* num_texture_formats */ 2,
        /* texture_formats */
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
        /* max_texture_width */ 3,
        /* max_texture_height */ 4
    };

    if (!PyArg_ParseTuple(args, ""))
        return NULL;

    return PyCSDL2_RendererInfoCreate(&info);
}

/**
 * \brief Sets the "name" field of the SDL_RendererInfo to "name".
 *
 * \code{.py}
 * rendererinfo_set_name(info: SDL_RendererInfo) -> None
 * \endcode
 */
static PyObject *
PyCSDL2Test_RendererInfoSetName(PyObject *module, PyObject *args)
{
    SDL_RendererInfo *info;

    if (!PyArg_ParseTuple(args, "O&", PyCSDL2_RendererInfoPtr, &info))
        return NULL;

    info->name = "name";

    Py_RETURN_NONE;
}

/**
 * \brief Creates a PyCSDL2_Renderer object.
 *
 * \code{.py}
 * renderer(deftarget: object) -> SDL_Renderer
 * \endcode
 */
static PyObject *
PyCSDL2Test_Renderer(PyObject *module, PyObject *args)
{
    SDL_Surface *surface;
    SDL_Renderer *renderer;
    PyObject *deftarget;

    if (!PyArg_ParseTuple(args, "O", &deftarget))
        return NULL;

    /*
     * NOTE: Since we allow the caller to specify the deftarget object, we will
     * leak this SDL_Surface. It's all for science though!
     */
    surface = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0);
    if (!surface) {
        PyErr_SetString(PyExc_RuntimeError, SDL_GetError());
        return NULL;
    }

    renderer = SDL_CreateSoftwareRenderer(surface);
    if (!renderer) {
        PyErr_SetString(PyExc_RuntimeError, SDL_GetError());
        return NULL;
    }

    return PyCSDL2_RendererCreate(renderer, deftarget);
}

/**
 * \brief Sets the render draw color of the SDL_Renderer to white.
 *
 * \code{.py}
 * renderer_set_draw_color(rdr: SDL_Renderer) -> None
 * \endcode
 */
static PyObject *
PyCSDL2Test_RendererSetDrawColor(PyObject *module, PyObject *args)
{
    SDL_Renderer *rdr;

    if (!PyArg_ParseTuple(args, "O&", PyCSDL2_RendererPtr, &rdr))
        return NULL;

    if (SDL_SetRenderDrawColor(rdr, 255, 255, 255, 255)) {
        PyErr_SetString(PyExc_RuntimeError, SDL_GetError());
        return NULL;
    }

    Py_RETURN_NONE;
}

/**
 * \brief Sets the render target of the SDL_Renderer
 *
 * \code{.py}
 * renderer_set_target(rdr: SDL_Renderer[, target: SDL_Texture]) -> None
 * \endcode
 */
static PyObject *
PyCSDL2Test_RendererSetTarget(PyObject *module, PyObject *args)
{
    SDL_Renderer *rdr;
    SDL_Texture *tex = NULL;

    if (!PyArg_ParseTuple(args, "O&|O&", PyCSDL2_RendererPtr, &rdr,
                          PyCSDL2_TexturePtr, &tex))
        return NULL;

    if (!tex) {
        tex = SDL_CreateTexture(rdr, SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET, 32, 32);
        if (!tex) {
            PyErr_SetString(PyExc_RuntimeError, SDL_GetError());
            return NULL;
        }
    }

    if (SDL_SetRenderTarget(rdr, tex)) {
        PyErr_SetString(PyExc_RuntimeError, SDL_GetError());
        return NULL;
    }

    Py_RETURN_NONE;
}

/**
 * \brief Creates a PyCSDL2_Texture object.
 *
 * \code{.py}
 * texture(renderer: SDL_Renderer) -> SDL_Texture
 * \endcode
 */
static PyObject *
PyCSDL2Test_Texture(PyObject *module, PyObject *args)
{
    SDL_Surface *surface;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    PyObject *rdr_obj;

    if (!PyArg_ParseTuple(args, "O", &rdr_obj))
        return NULL;

    /*
     * NOTE: Since we allow the caller to specify the renderer object, we will
     * leak the surface and renderer we create here. It's all for science
     * though!
     */

    surface = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0);
    if (!surface)
        goto fail;

    renderer = SDL_CreateSoftwareRenderer(surface);
    if (!renderer) {
        SDL_FreeSurface(surface);
        goto fail;
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_STATIC, 32, 32);
    if (!texture) {
        SDL_DestroyRenderer(renderer);
        SDL_FreeSurface(surface);
        goto fail;
    }

    return PyCSDL2_TextureCreate(texture, rdr_obj);

fail:
    PyErr_SetString(PyExc_RuntimeError, SDL_GetError());
    return NULL;
}

/**
 * \brief Returns the SDL_Texture format
 *
 * \code{.py}
 * texture_get_format(texture: SDL_Texture) -> int
 * \endcode
 */
static PyObject *
PyCSDL2Test_TextureGetFormat(PyObject *module, PyObject *args)
{
    SDL_Texture *texture;
    Uint32 format;

    if (!PyArg_ParseTuple(args, "O&", PyCSDL2_TexturePtr, &texture))
        return NULL;

    if (SDL_QueryTexture(texture, &format, NULL, NULL, NULL)) {
        PyErr_SetString(PyExc_RuntimeError, SDL_GetError());
        return NULL;
    }

    return PyLong_FromUnsignedLong(format);
}

#endif /* _PYCSDL2TEST_RENDER_H_ */
