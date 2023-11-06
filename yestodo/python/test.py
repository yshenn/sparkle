import pytermgui as ptg

with ptg.alt_buffer():
    root = ptg.Container(
        ptg.Label("[italic 141 bold]This is some [green]fancy [white inverse]text!")
    )
    root.print()
    ptg.getch()
