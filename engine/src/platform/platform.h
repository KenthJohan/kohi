/**
 * @file platform.h
 * @author Travis Vroman (travis@kohiengine.com)
 * @brief This file contains the platform layer, or at least the interface to it.
 * Each platform should provide its own implementation of this in a .c file, and
 * should be compiled exclusively of the rest.
 * @version 1.0
 * @date 2022-01-10
 *
 * @copyright Kohi Game Engine is Copyright (c) Travis Vroman 2021-2022
 *
 */

#pragma once

#include "defines.h"

typedef struct platform_system_config {
    /** @brief application_name The name of the application. */
    const char* application_name;
    /** @brief x The initial x position of the main window. */
    i32 x;
    /** @brief y The initial y position of the main window.*/
    i32 y;
    /** @brief width The initial width of the main window. */
    i32 width;
    /** @brief height The initial height of the main window. */
    i32 height;
} platform_system_config;

/**
 * @brief Performs startup routines within the platform layer. Should be called twice,
 * once to obtain the memory requirement (with state=0), then a second time passing
 * an allocated block of memory to state.
 *
 * @param memory_requirement A pointer to hold the memory requirement in bytes.
 * @param state A pointer to a block of memory to hold state. If obtaining memory requirement only, pass 0.
 * @param config A pointer to a configuration platform_system_config structure required by this system.
 * @return True on success; otherwise false.
 */
b8 platform_system_startup(u64* memory_requirement, void* state, void* config);

/**
 * @brief Shuts down the platform layer.
 *
 * @param plat_state A pointer to the platform layer state.
 */
void platform_system_shutdown(void* plat_state);

/**
 * @brief Performs any platform-specific message pumping that is required
 * for windowing, etc.
 *
 * @return True on success; otherwise false.
 */
b8 platform_pump_messages();

/**
 * @brief Performs platform-specific memory allocation of the given size.
 *
 * @param size The size of the allocation in bytes.
 * @param aligned Indicates if the allocation should be aligned.
 * @return A pointer to a block of allocated memory.
 */
void* platform_allocate(u64 size, b8 aligned);

/**
 * @brief Frees the given block of memory.
 *
 * @param block The block to be freed.
 * @param aligned Indicates if the block of memory is aligned.
 */
void platform_free(void* block, b8 aligned);

/**
 * @brief Performs platform-specific zeroing out of the given block of memory.
 *
 * @param block The block to be zeroed out.
 * @param size The size of data to zero out.
 * @return A pointer to the zeroed out block of memory.
 */
void* platform_zero_memory(void* block, u64 size);

/**
 * @brief Copies the bytes of memory in source to dest, of the given size.
 *
 * @param dest The destination memory block.
 * @param source The source memory block.
 * @param size The size of data to be copied.
 * @return A pointer to the destination block of memory.
 */
void* platform_copy_memory(void* dest, const void* source, u64 size);

/**
 * @brief Sets the bytes of memory to the given value.
 *
 * @param dest The destination block of memory.
 * @param value The value to be set.
 * @param size The size of data to set.
 * @return A pointer to the set block of memory.
 */
void* platform_set_memory(void* dest, i32 value, u64 size);

/**
 * @brief Performs platform-specific printing to the console of the given
 * message and colour code (if supported).
 *
 * @param message The message to be printed.
 * @param colour The colour to print the text in (if supported).
 */
void platform_console_write(const char* message, u8 colour);

/**
 * @brief Performs platform-specific printing to the error console of the given
 * message and colour code (if supported).
 *
 * @param message The message to be printed.
 * @param colour The colour to print the text in (if supported).
 */
void platform_console_write_error(const char* message, u8 colour);

/**
 * @brief Gets the absolute time since the application started.
 *
 * @return The absolute time since the application started.
 */
f64 platform_get_absolute_time();

/**
 * @brief Sleep on the thread for the provided milliseconds. This blocks the main thread.
 * Should only be used for giving time back to the OS for unused update power.
 * Therefore it is not exported. Times are approximate.
 *
 * @param ms The number of milliseconds to sleep for.
 */
void platform_sleep(u64 ms);

/**
 * @brief Obtains the number of logical processor cores.
 *
 * @return The number of logical processor cores.
 */
i32 platform_get_processor_count();

/**
 * @brief Obtains the required memory amount for platform-specific handle data,
 * and optionally obtains a copy of that data. Call twice, once with memory=0
 * to obtain size, then a second time where memory = allocated block.
 *
 * @param out_size A pointer to hold the memory requirement.
 * @param memory Allocated block of memory.
 */
KAPI void platform_get_handle_info(u64* out_size, void* memory);
