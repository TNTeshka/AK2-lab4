// SPDX-License-Identifier: Dual BSD/GPL
/*
 * Copyright (c) 2017, GlobalLogic Ukraine LLC
 * All rights reserved.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/param.h>

MODULE_AUTHOR("Pavlyuk Nazar <pupikpn@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training with parameter support");
MODULE_LICENSE("Dual BSD/GPL");

// Параметр для кількості повторів "Hello, world!"
static uint hello_count = 1;
module_param(hello_count, uint, 0444);
MODULE_PARM_DESC(hello_count, "Number of times to print 'Hello, world!'");

// Функція ініціалізації модуля
static int __init hello_init(void)
{
	int i;

	/* Перевірка значення параметра */
	if (hello_count == 0 || (hello_count >= 5 && hello_count <= 10))
		pr_warn("Warning: hello_count is 0 or between 5 and 10. Continuing...\n");

	if (hello_count > 10) {
		pr_err("Error: hello_count > 10. Module not loaded.\n");
		/* Повертаємо помилку: модуль */
		/* не буде завантажено */
		return -EINVAL;
	}

	/* Друк "Hello, world!" hello_count разів */
	for (i = 0; i < hello_count; i++)
		pr_info("Hello, world! (%d)\n", i + 1);

	return 0;
}

// Функція завершення модуля
static void __exit hello_exit(void)
{
	pr_info("Goodbye, world!\n");
}

module_init(hello_init);
module_exit(hello_exit);
