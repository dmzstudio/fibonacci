/******************************************************************************
 *
 * Fibonacci Series
 *
 * Author: NagaChaitanya Vellanki
 *
 * ***************************************************************************/

#include "ruby.h"

#define ONE INT2NUM(1)
#define ZERO INT2NUM(0)
#define TWO INT2NUM(2)

static VALUE cFibonacci;
static VALUE id_plus;
static VALUE id_lte;
static VALUE id_lt;
static VALUE id_pow; 
static VALUE id_minus; 
static VALUE id_fdiv; 
static VALUE id_to_i; 
static VALUE id_log10;
static VALUE id_floor;
static VALUE id_sqrt; 
static VALUE id_mul; 
static VALUE id_eq; 


static VALUE
fibonacci_init(VALUE self)
{
	return self;
}

static VALUE
print_num(VALUE self, VALUE num)
{
	VALUE num_str =  rb_funcall(num, rb_intern("to_s"), 0);
	char *cptr = StringValuePtr(num_str);
	printf("%s\n", cptr);
	return Qnil;
}

static VALUE
print(VALUE self, VALUE n)
{
	VALUE start = ZERO;
	VALUE fib_n_1 = ONE;
	VALUE fib_n_2 = ONE;
	VALUE fib_n = ZERO;

	if(TYPE(n) != T_FIXNUM)
	{
		rb_raise(rb_eArgError, "Invalid argument for type Fixnum");
		return Qnil;
	}

	for(start; Qtrue == rb_funcall(start, id_lt, 1, n); start = rb_funcall(start, id_plus, 1, ONE))
	{
		if(Qtrue == rb_funcall(start, id_eq, 1, ZERO))
		{
			print_num(self, ZERO);
		}
		else if(Qtrue == rb_funcall(start, id_lte, 1, TWO))
		{
			print_num(self, ONE);
		}
		else
		{
			fib_n = rb_funcall(fib_n_1, id_plus, 1, fib_n_2);
			fib_n_2 = fib_n_1;
			fib_n_1 = fib_n;
			print_num(self, fib_n);
		}
	}

	return Qnil;
}

static VALUE
index_of(VALUE self, VALUE val)
{
	return Qnil;
}

static VALUE
num_digits(VALUE self, VALUE i)
{
	if(Qtrue == rb_funcall(i, id_lt, 1, ZERO))
	{
		rb_raise(rb_eArgError, "index cannot be negative");
		return Qnil;
	}
	else
	{
		VALUE phi = ONE;
		VALUE num_digits = ZERO;
		VALUE log_sqrt_5 = ZERO;

		VALUE sqrt_5 = rb_funcall(rb_mMath, id_sqrt, 1, INT2NUM(5));
		log_sqrt_5 = rb_funcall(rb_mMath, id_log10, 1, sqrt_5);

		phi = rb_funcall(phi, id_plus, 1, sqrt_5);
		phi = rb_funcall(phi, id_fdiv, 1, TWO);

		num_digits = rb_funcall(rb_mMath, id_log10, 1, phi);
		num_digits = rb_funcall(num_digits, id_mul, 1, i);
		num_digits = rb_funcall(num_digits, id_minus, 1, log_sqrt_5);

		num_digits = rb_funcall(num_digits, id_floor, 0);
		num_digits = rb_funcall(num_digits, id_plus, 1, ONE);
		num_digits = rb_funcall(num_digits, id_to_i, 0);

		return num_digits;
	}
}

void
Init_fibonacci(void)
{
	id_plus = rb_intern("+");
	id_lte = rb_intern("<=");
	id_lt = rb_intern("<");
	id_pow = rb_intern("**");
	id_mul = rb_intern("*");
	id_minus = rb_intern("-");
	id_fdiv = rb_intern("fdiv");
	id_to_i = rb_intern("to_i");
	id_log10 = rb_intern("log10");
	id_floor = rb_intern("floor");
	id_sqrt = rb_intern("sqrt");
	id_eq = rb_intern("==");

	cFibonacci = rb_define_class("Fibonacci", rb_cObject);
	rb_define_method(cFibonacci, "initialize", fibonacci_init, 0);
	rb_define_private_method(cFibonacci, "print_num", print_num, 1);
	rb_define_method(cFibonacci, "print", print, 1);
	rb_define_method(cFibonacci, "index_of", index_of, 1);
	rb_define_method(cFibonacci, "num_digits", num_digits, 1);
}
