include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/DropdownExample.re').default|}] |> Examples.prepCode;

let se = React.string;

type state = {isOpen: bool};

type actions =
  | Toggle;


let toggle =
    (dispatch, ()) => {
  dispatch(Toggle);
};

let initialState = {isOpen: false};

let reducer = (state, action) : state => {
switch (action) {
    | Toggle => {isOpen: !state.isOpen}
    }
};

[@react.component]
let make = () => {
  
    let (state, dispatch) = React.useReducer(reducer, initialState);

    <Examples.Example title="Dropdowns">
      <Dropdown isOpen=state.isOpen>
        <Dropdown.Toggle
          isOpen=state.isOpen caret=true toggle=(toggle(dispatch))>
          (se("align right! "))
        </Dropdown.Toggle>
        <Dropdown.Menu isOpen=state.isOpen alignRight=true>
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
    </Examples.Example>
};
