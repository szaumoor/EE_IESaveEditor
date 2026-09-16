#ifndef EE_SAVEEDITOR_IE_CLASS_H
#define EE_SAVEEDITOR_IE_CLASS_H

/**
 * Empty struct to define a no-storage cost, zero-overhead interface for all other IE-related
 * classes. This exists purely as a convenience to tag domain types.
 */
struct IEClass {
protected:
    IEClass() = default;
};

#endif //EE_SAVEEDITOR_IE_CLASS_H
