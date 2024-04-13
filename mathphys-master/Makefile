compiler = g++
excutable = mathphys.x
headfile = $(shell find src/ -maxdepth 1 -name "*.h")
src = $(shell find src/ -maxdepth 1 -name "*.cpp")
obj = $(src:%.cpp=%.o)
lapack_flag = -llapack -lblas
openmp_flag = -fopenmp
c++stdflag = -std=c++11
compileflag = -O1
gdbflag = -g
$(excutable) : $(obj)
	$(compiler) -o $(excutable) $(obj) $(lapack_flag) $(openmp_flag) $(gdbflag) $(compileflag)

%.o : %.cpp $(headfile)
	$(compiler) -c $< -o $@ $(openmp_flag) $(c++stdflag) $(gdbflag) $(compileflag) -w

clean:
	rm -rf $(obj) $(excutable)
	rm output/* ; touch output/test
	rm doc/tex/*.aux doc/tex/*.log doc/tex/*.nav doc/tex/*.out doc/tex/*.snm doc/tex/*.gz doc/tex/*.toc
	rm warehouse/old-src/*.out
