// READ THE HEADER FILE FOR MORE DOCUMENTATION
#include "tl04.h"


/**
 * \brief Pointers to the ends of the list
 *
 * These pointers keep track of where the singly-linked list is in memory. The
 * [queue_head] pointer points to the first node of the list, and [queue_tail]
 * likewise points to the last.
 *
 * Initially, both of these pointers are `NULL`. The list is initially empty, so
 * there is no first or last node.
 *
 * \property extern queue_node_t *queue_head
 * \property extern queue_node_t *queue_tail
 */
struct queue_node_t *queue_head = NULL;
struct queue_node_t *queue_tail = NULL;


/**
 * \brief Add students to the queue
 *
 * This function will be called by client code to add a student to the end of
 * the queue. The caller will supply the data of the student to add.
 *
 * This function should allocate a [queue_node_t] on the heap, and deep-copy
 * all the other data. In particular, any pointers in the [queue_node_t] will
 * require their own dedicated memory allocation.
 * 
 * Note: Make sure that all members of the [queue_node_t] are set!
 * 
 * Finally, insert the student into the queue with the help of the [queue_head]
 * and/or [queue_tail] pointers.
 * 
 * Refer back to the PDF/diagram for specific details about how to link the
 * nodes, and consider any edge cases.
 *
 * This function should return `SUCCESS` if the student was added successfully.
 * If it fails, it should return `FAILURE` and leave the list unchanged. It
 * should fail if and only if:
 * * `malloc` fails,
 * * the student's name is `NULL`, or
 * * the student's name is an empty string.
 *
 * \param[in] data Data of the student to enqueue
 * \return Whether the student was successfully added
 */
int queue_add(struct student_t data) {
    // TODO
    //UNUSED(data);
    if (data.name == NULL || strlen(data.name) == 0) {
        return FAILURE;
    }
    struct queue_node_t *student = malloc(sizeof(struct queue_node_t));
    if (!student) {
        free(student);
        return FAILURE;
    }
    student->data.name = malloc((sizeof(char) * strlen(data.name)) + 1);
    if (!student->data.name) {
        free(student->data.name);
        free(student);
        return FAILURE;
    } else {
        strcpy(student->data.name, data.name);
    }
    student->data.assignment = data.assignment;
    if (!queue_head && !queue_tail) {
        queue_head = student;
        queue_tail = student;
        queue_head->next = NULL;
        queue_tail->next = NULL;
    } else {
        queue_tail->next = student;
        queue_tail = student;
        queue_tail->next = NULL;
    }
    return SUCCESS;
}

/**
 * \brief Remove students from the queue
 *
 * This function will be called by client code to remove a student from the
 * front the queue. It will return whether a student was removed successfully,
 * and the data removed in that case.
 *
 * The way this function returns the student data using the data out technique.
 * This is to get around the limitation that functions may only have one return
 * value. As such, the caller will pass in a pointer where the student's data
 * should be stored. Then this function will store the returned data at that
 * pointer. Independently, it returns whether it succeeded via the normal path.
 * 
 * Finally, remove the student into the queue with the help of the [queue_head]
 * and/or [queue_tail] pointers.
 * 
 * Refer back to the PDF/diagram for specific details about how to link the
 * nodes, and consider any edge cases.
 * 
 * Remember to free the node when you're done. A copy of the data is being
 * returned, the node containing the data is not. The node will no longer be
 * accessible when the function returns, so it should be freed.
 *
 * If this function succeeds, it should return `SUCCESS` and modify `*data` to
 * be the data of the student removed. If it fails, it should return `FAILURE`
 * and leave both the list and `*data` unchanged. It should fail if and only if:
 * * [data] is `NULL`, or
 * * the list is empty.
 *
 * \param[out] data Where to put the data of the removed student
 * \return Whether a student was successfully removed
 */
int queue_remove(struct student_t *data) {
    // TODO
    //UNUSED(data);
    if (!data || !queue_head) {
        return FAILURE;
    } else {
        struct queue_node_t *temp = queue_head;
        *data = temp->data;
        queue_head = queue_head->next;
        if (!queue_head) {
            queue_tail = NULL;
        }
        free(temp);
    }
    return SUCCESS;
}
