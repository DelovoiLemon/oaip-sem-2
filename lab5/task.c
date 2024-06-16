#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int max_length;
char tree_draw_helper[] = "/ \\";

typedef struct Tree {
  int value;
  char *name;
  struct Tree *left, *right;
} tree;

typedef struct NameValue {
  int val;
  char *name;
} nameVal;

typedef int (*tree_cmp)(const tree *node, const int value, const char *name,
                        const tree *ptr);

tree *list(const int value, const char *name) {
  tree *t = malloc(sizeof(tree));
  t->value = value;
  t->left = t->right = NULL;
  t->name = strdup(name);
  return t;
}

int isExisting(const tree *root, const int key) {
  return (root ? (key == root->value ? 1
                                     : isExisting(root->left, key) +
                                           isExisting(root->right, key))
               : 0);
}
void add_list(tree **root, const int value, const char *name) {
  if (!(*root)) {
    *root = list(value, name);
    return;
  }
  if (isExisting(*root, value)) {
    printf("Duplicated value\n");
    return;
  }
  if (((*root)->value) > value)
    add_list(&((*root)->left), value, name);
  else
    add_list(&((*root)->right), value, name);
}

void concat(char *target, const char *source) {
  if (!target || !source)
    return;
  for (; *target; target++)
    ;
  for (; *source; source++, target++)
    *target = *source;
  *target = '\0';
}

int digits_count(int val) {
  int i = 1;
  for (val /= 10; val; i++, val /= 10)
    ;
  return i;
}

int get_tree_length(const tree *root) {
  int left_len, right_len;
  if (!root)
    return 0;

  left_len = get_tree_length(root->left);
  right_len = get_tree_length(root->right);

  return 1 + ((left_len > right_len) ? left_len : right_len);
}

int twoinpower(int power) { return 1 << power; }

int tree_to_strs(tree *root, char **strs, int dist_to_peek, int direction,
                 const char *separator, const int max_len) {
  char *tmp;
  int d_count, padding_left = 0, padding_right = 0, width = max_len;
  if (root) {
    tmp = malloc(twoinpower(dist_to_peek) * max_len * sizeof(char));
    d_count = digits_count(root->value);
    padding_left = tree_to_strs(root->left, strs + 1, dist_to_peek - 1,
                                direction, separator, max_len);
    padding_right = tree_to_strs(root->right, strs + 1, dist_to_peek - 1,
                                 direction, separator, max_len);
    width = padding_left + padding_right - d_count - 2;
    sprintf(tmp, "%*s%c%i%c%*s", (width / 2) + (width % 2), "",
            tree_draw_helper[1 - direction * !(!root->left)], root->value,
            tree_draw_helper[1 + direction * !(!root->right)], (width / 2), "");
    concat(*strs, tmp);
    free(tmp);

    return padding_left + padding_right;
  }
  if (dist_to_peek > 1)
    width = tree_to_strs(NULL, strs + 1, dist_to_peek - 1, direction, separator,
                         max_len);
  if (dist_to_peek > 0) {
    concat(*strs, separator);
  }
  return width;
}

int get_max(tree *root) {
  if (!root)
    return 0;
  return root->right ? get_max(root->right) : root->value;
}

void view_tree(tree *root, int direction) {
  int max_num_len = digits_count(get_max(root)) + 2;
  int dist_to_peek = get_tree_length(root) + 1;
  char **strs = malloc((dist_to_peek) * sizeof(char *));
  int str_size = twoinpower(dist_to_peek) * max_num_len;
  for (int i = 0; i < dist_to_peek; i++) {
    strs[i] = malloc(str_size * sizeof(char));
    strs[i][0] = 0;
  }
  char *separ = malloc((max_num_len + 1) * sizeof(char));
  for (int i = 0; i < max_num_len; i++)
    separ[i] = ' ';

  separ[max_num_len] = '\0';

  tree_to_strs(root, strs, dist_to_peek, direction, separ, max_num_len);

  for (int i = (direction > 0) ? 0 : (dist_to_peek - 2);
       (direction > 0) ? (i < dist_to_peek - 1) : (i >= 0); i += direction) {
    puts(strs[i]);
    free(strs[i]);
  }
  free(strs);
}

tree *del_by_key(tree *root, const int key) {
  tree *del, *del_prev, *r, *r_prev;
  del = root;
  del_prev = NULL;

  while (del != NULL && del->value != key) {
    del_prev = del;
    del = (del->value > key) ? del->left : del->right;
  }

  if (del == NULL) {
    puts("Key not found!");
    return root;
  }

  if (del->left == NULL)
    r = del->right;
  else if (del->right == NULL)
    r = del->left;
  else {
    r_prev = del;
    r = del->left;
    while (r->right != NULL)
      r_prev = r, r = r->right;

    if (r_prev == del)
      r->right = del->right;
    else {
      r->right = del->right;
      r_prev->right = r->left;
      r->left = r_prev;
    }
  }

  if (del == root)
    root = r;
  else if (del->value < del_prev->value)
    del_prev->left = r;
  else
    del_prev->right = r;

  free(del);
  return root;
}

void del_tree(tree *root) {
  if (root) {
    del_tree(root->left);
    del_tree(root->right);
    free(root);
  }
}

tree *sorted_arr_to_tree(nameVal *arr, int len) {
  int center = len / 2;
  if (len <= 0)
    return NULL;
  tree *t = list(arr[center].val, arr[center].name);
  if (len > 1) {
    t->left = sorted_arr_to_tree(arr, center);
    t->right = sorted_arr_to_tree(arr + center + 1, len - center - 1);
  }
  return t;
}

tree *find_node_by_key(tree *root, int key) {
  if (!root)
    return NULL;
  if (root->value == key)
    return root;
  return (root->value > key) ? find_node_by_key(root->left, key)
                             : find_node_by_key(root->right, key);
}

void print_tree_straight(tree *root) {
  if (root) {
    printf("%i: %s\n", root->value, root->name);
    print_tree_straight(root->left);
    print_tree_straight(root->right);
  }
}

void print_tree_reverse(tree *root) {
  if (root) {
    print_tree_reverse(root->left);
    print_tree_reverse(root->right);
    printf("%i: %s\n", root->value, root->name);
  }
}
void print_tree_middle(tree *root) {
  if (root) {
    print_tree_middle(root->left);
    printf("%i: %s\n", root->value, root->name);
    print_tree_middle(root->right);
  }
}

/* tree_cmp must return
 * -1 root's val is less
 *  0 root's val is equal
 * +1 root's val is more
 *
 */

int compare_name_starts_with(const tree *root, const int value,
                             const char *name, const tree *ptr) {
  int i = 0;
  if (!root)
    return -2;
  while (name[i] && root->name[i] == name[i])
    i++;
  return root->name[i] == name[i] ? 0 : root->name[i] > name[i] ? 1 : -1;
}

// Returns true if root->name contains name
int compare_name_lightly(const tree *root, const int value, const char *name,
                         const tree *ptr) {
  int i = 0;
  if (!root)
    return -2;
  while (name[i] && root->name[i] == name[i])
    i++;
  return root->name[i] == name[i] ? 0 : root->name[i] > name[i] ? 1 : -1;
}

int check_starts_with_a(const tree *root, const int value, const char *name,
                        const tree *ptr) {
  return (root && root->name) ? (root->name[0] == 'a' || root->name[0] == 'A')
                              : 0;
}

int tree_counter(const tree *root, const tree_cmp cmp, const int value,
                 const char *name, const tree *ptr, const int mode) {
  if (!root)
    return 0;

  return (cmp(root, value, name, ptr) == mode) +
         tree_counter(root->left, cmp, value, name, ptr, mode) +
         tree_counter(root->right, cmp, value, name, ptr, mode);
}

void view_filtered(const tree *root, const tree_cmp cmp, const int value,
                   const char *name, const tree *ptr, const int mode) {
  if (!root)
    return;

  view_filtered(root->left, cmp, value, name, ptr, mode);
  if (cmp(root, value, name, ptr))
    printf("%i: %s\n", root->value, root->name);
  view_filtered(root->right, cmp, value, name, ptr, mode);
}

int get_count(const tree *root) {
  return root ? 1 + get_count(root->left) + get_count(root->right) : 0;
}

int tree_to_arr(const tree *root, nameVal *arr) {
  int index = 0;
  if (!root)
    return 0;

  index = tree_to_arr(root->left, arr);
  arr[index].val = root->value;
  arr[index].name = root->name;
  index += tree_to_arr(root->right, arr + index + 1);
  return index + 1;
}

int main() {
  tree *root = NULL;
  int choice;
  int value;
  char name[15];
  while (1) {
    printf("Menu:\n");
    printf("1. Add element to the tree\n");
    printf("2. Create random tree\n");
    printf("3. View tree\n");
    printf("4. Print tree straight\n");
    printf("5. Print tree reverse\n");
    printf("6. Print tree in order\n");
    printf("7. Count names starting with 'a'\n");
    printf("8. View filtered tree\n");
    printf("9. Sort tree and view\n");
    printf("10. Delete node by key\n");
    printf("11. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      printf("Enter value: ");
      scanf("%d", &value);
      printf("Enter name: ");
      scanf("%s", name);
      add_list(&root, value, name);
      break;
    case 2: {
      int count = 10;
      const char *names[15] = {"Andrew", "Aleksey", "Akakiy",  "Boris",
                               "Vicror", "Georgiy", "Dmitriy", "Evgeniy",
                               "Zhorik", "Zina",    "Irina",   "Katya",
                               "Lena",   "Michail"};
      for (int i = 0; i < count; i++) {
        value = rand();
        add_list(&root, value, names[rand() % 15]);
      }
    } break;
    case 3:
      view_tree(root, 1);
      break;
    case 4:
      print_tree_straight(root);
      break;
    case 5:
      print_tree_reverse(root);
      break;
    case 6:
      print_tree_middle(root);
      break;
    case 7:
      printf("Amount of names starting with 'a': %i\n",
             tree_counter(root, check_starts_with_a, 0, 0, 0, 1));
      break;
    case 8:
      view_filtered(root, check_starts_with_a, 0, 0, 0, 1);
      break;
    case 9: {
      int c = get_count(root);
      nameVal *array = malloc(c * sizeof(nameVal));
      tree_to_arr(root, array);
      tree *tmp = sorted_arr_to_tree(array, c);
      view_tree(tmp, -1);
      puts("\n");
      view_tree(tmp, 1);
      del_tree(tmp);
      free(array);
    } break;
    case 10: {
      int key;
      printf("Enter key to delete: ");
      scanf("%d", &key);
      root = del_by_key(root, key);
      break;
    }
    case 11: {
      del_tree(root);
      return 0;
    }
    default:
      printf("Invalid choice\n");
    }
  }
  return 0;
}