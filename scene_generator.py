import random

def init_light(x_range, y_range, z_range, brightness, color_range):
	x = random.uniform(x_range[0], x_range[1])
	y = y_range[1] * 4
	z = random.uniform(z_range[0], z_range[1])
	r = random.randint(color_range[0], color_range[1])
	g = random.randint(color_range[0], color_range[1])
	b = random.randint(color_range[0], color_range[1])
	light = f"L   {x:.2f},{y:.2f},{z:.2f}  {brightness}  {r},{g},{b}"
	print(light)
	print(f"A {ambient_intensity} {r},{g},{b}")

def generate_spheres(n, x_range, y_range, z_range, diameter_range, color_range):
	for _ in range(n):
		x = random.uniform(x_range[0], x_range[1])
		y = random.uniform(y_range[0], y_range[1])
		z = random.uniform(z_range[0], z_range[1])
		diameter = random.uniform(diameter_range[0], diameter_range[1])
		r = random.randint(color_range[0], color_range[1])
		g = random.randint(color_range[0], color_range[1])
		b = random.randint(color_range[0], color_range[1])
		sphere = f"sp   {x:.2f},{y:.2f},{z:.2f}   {diameter:.2f}   {r},{g},{b}"
		print(sphere)

def init_camera(x_range, y_range):
	x = x_range[0] + x_range[1]
	y = y_range[0] + y_range[1]
	z = 40
	fov = 30
	lookat_x = 0
	lookat_y = 0
	lookat_z = -1
	camera = f"C   {x},{y},{z}   {lookat_x},{lookat_y},{lookat_z}  {fov}"
	print(camera)

x_range = (-25, 25)
y_range = (-15, 15)
z_range = (-5, -12)
diameter_range = (0.2, 3)
brightness = 1.0
color_range = (0, 255)
n_spheres = 60
ambient_intensity = 0.1

init_camera(x_range, y_range)
init_light(x_range, y_range, z_range, brightness, color_range)
print()
generate_spheres(n_spheres, x_range, y_range, z_range, diameter_range, color_range)