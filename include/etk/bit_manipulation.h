#ifndef _ETK_BIT_MANIPULATION_H_
#define _ETK_BIT_MANIPULATION_H_

/**
 * @brief Set a bit in a variable.
 *
 * This macro sets the bit at position `bit` in the variable `val`.
 *
 * @param val The variable in which the bit is to be set.
 * @param bit The position of the bit to be set.
 */
#define SET_BIT(val, bit) ((val) |= (1 << (bit)))

/**
 * @brief Clear a bit in a variable.
 *
 * This macro clears the bit at position `bit` in the variable `val`.
 *
 * @param val The variable in which the bit is to be cleared.
 * @param bit The position of the bit to be cleared.
 */
#define CLEAR_BIT(val, bit) ((val) &= ~(1 << (bit)))

/**
 * @brief Toggle a bit in a variable.
 *
 * This macro toggles the bit at position `bit` in the variable `val`.
 *
 * @param val The variable in which the bit is to be toggled.
 * @param bit The position of the bit to be toggled.
 */
#define TOGGLE_BIT(val, bit) ((val) ^= (1 << (bit)))

/**
 * @brief Set bits in a variable according to a mask.
 *
 * This macro sets the bits in the variable `val` according to the bitmask
 * `mask`.
 *
 * @param val The variable in which the bits are to be set.
 * @param mask The bitmask indicating which bits to set.
 */
#define BITMASK_SET(val, mask) ((val) |= (mask))

/**
 * @brief Clear bits in a variable according to a mask.
 *
 * This macro clears the bits in the variable `val` according to the bitmask
 * `mask`.
 *
 * @param val The variable in which the bits are to be cleared.
 * @param mask The bitmask indicating which bits to clear.
 */
#define BITMASK_CLEAR(val, mask) ((val) &= ~(mask))

/**
 * @brief Toggle bits in a variable according to a mask.
 *
 * This macro toggles the bits in the variable `val` according to the bitmask
 * `mask`.
 *
 * @param val The variable in which the bits are to be toggled.
 * @param mask The bitmask indicating which bits to toggle.
 */
#define BITMASK_TOGGLE(val, mask) ((val) ^= (mask))

/**
 * @brief Check if a bit is set in a variable.
 *
 * This macro checks if the bit at position `bit` in the variable `val` is set.
 *
 * @param val The variable to be checked.
 * @param bit The position of the bit to be checked.
 * @return TRUE if the bit is set, FALSE otherwise.
 */
#define BIT_IS_SET(val, bit) ((val) & (1 << (bit))) ? TRUE : FALSE

/**
 * @brief Check if a bit is cleared in a variable.
 *
 * This macro checks if the bit at position `bit` in the variable `val` is
 * cleared.
 *
 * @param val The variable to be checked.
 * @param bit The position of the bit to be checked.
 * @return TRUE if the bit is cleared, FALSE otherwise.
 */
#define BIT_IS_CLEAR(val, bit) ((val) & (1 << (bit))) ? FALSE : TRUE

/**
 * @brief Check if bits are set in a variable according to a mask.
 *
 * This macro checks if the bits in the variable `val` are set according to the
 * bitmask `mask`.
 *
 * @param val The variable to be checked.
 * @param mask The bitmask indicating which bits to check.
 * @return TRUE if the bits are set according to the mask, FALSE otherwise.
 */
#define BITMASK_IS_SET(val, mask) ((val) & (mask)) ? TRUE : FALSE

/**
 * @brief Check if bits are cleared in a variable according to a mask.
 *
 * This macro checks if the bits in the variable `val` are cleared according to
 * the bitmask `mask`.
 *
 * @param val The variable to be checked.
 * @param mask The bitmask indicating which bits to check.
 * @return TRUE if the bits are cleared according to the mask, FALSE otherwise.
 */
#define BITMASK_IS_CLEAR(val, mask) ((val) & (mask)) ? FALSE : TRUE

#endif /* _ETK_BIT_MANIPULATION_H_ */