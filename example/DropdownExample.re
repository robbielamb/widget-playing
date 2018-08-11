include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/DropdownExample.re')|}] |> Examples.prepCode;

let se = ReasonReact.string;

type state = {isOpen: bool};

type actions =
  | Toggle;

let component = ReasonReact.reducerComponent("DropdownExample");

let toggle =
    (self: ReasonReact.self(state, ReasonReact.noRetainedProps, actions), ()) => {
  Js.log("toggling");
  self.send(Toggle);
};

let make = _children => {
  ...component,
  initialState: () => {isOpen: false},
  reducer: (action, state) =>
    switch (action) {
    | Toggle => ReasonReact.Update({isOpen: !state.isOpen})
    },
  render: self =>
    <Examples.Example title="Dropdowns">
      <Dropdown isOpen=self.state.isOpen toggle=(toggle(self))>
        <Dropdown.Toggle
          isOpen=self.state.isOpen caret=true toggle=(toggle(self))>
          (se("align right! "))
        </Dropdown.Toggle>
        <Dropdown.Menu isOpen=self.state.isOpen alignRight=true>
          <Dropdown.Header> (se("Header")) </Dropdown.Header>
          <Dropdown.Item> (se("Another Action")) </Dropdown.Item>
          <Dropdown.Item disabled=true>
            (se("Disabled Action"))
          </Dropdown.Item>
          <Dropdown.Item> (se("Another Item")) </Dropdown.Item>
          <Dropdown.Divider />
          <Dropdown.Item> (se("Last Item")) </Dropdown.Item>
        </Dropdown.Menu>
      </Dropdown>
      (Examples.exampleHighlight(code))
    </Examples.Example>,
};
