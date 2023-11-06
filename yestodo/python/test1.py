from pytermgui import Container, SizePolicy, pretty, alt_buffer, getch

with alt_buffer():
    container = Container(
        Container("I fill the space"),
        Container("I take up 70%", relative_width=0.7),
        Container("I take up exactly\n 31characters", static_width=31),
    )
    container.print()
    getch()
