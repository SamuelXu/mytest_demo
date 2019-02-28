package main

import "fmt"

type Student struct {
	Name string
	Stu  *Student
}

func main() {
	var s *Student = new(Student)
	var t *Student = new(Student)

	s.Name = "jack"
	s.Stu = new(Student)
	s.Stu.Name = "jack1"
	*t = *s
	fmt.Println("t=", t, t.Stu, "s=", s, s.Stu)
	s.Name = "rose"
	t.Stu.Name = "rose1"
	fmt.Println("t=", t, t.Stu, "s=", s, s.Stu)

	fmt.Println("============")
	s.Name = "jack"
	t = s
	fmt.Println("t=", t, t.Stu, "s=", s, s.Stu)
	s.Name = "rose"
	t.Stu.Name = "jack1"
	fmt.Println("t=", t, t.Stu, "s=", s, s.Stu)
}
