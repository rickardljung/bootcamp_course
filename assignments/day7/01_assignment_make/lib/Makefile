compiler = g++

libshape.so: shapes.cpp shape_interface.cpp
	$(compiler) --shared -fPIC shapes.cpp shape_interface.cpp -o libshape.so

clean:
	rm libshape.so