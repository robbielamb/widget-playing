include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/TabsExample.re').default|}] |> Examples.prepCode;

let se = React.string;

type tabs =
  | Tab1
  | Tab2;
type state = {activeTab: tabs};
type action =
  | SwitchTab(tabs);

let  initialState = {activeTab: Tab1};

let reducer = (_state, action) => {
switch (action) {
    | SwitchTab(newTab) => {activeTab: newTab}
    }
};


[@react.component]
let make = () => {
    let (state, dispatch) = React.useReducer(reducer, initialState);

    let panels = [|
      Tab.Pane.create(~tabId=Tab1, ~key="1", se("Something here")),
      Tab.Pane.create(~tabId=Tab2, ~key="2", se("Something else")),
    |];
    <Examples.Example title="Tabs Example">
      <div>
        <Nav tabs=true>
          <Nav.Item>
            <Nav.Link
              active=(state.activeTab == Tab1)
              onClick=(_event => dispatch(SwitchTab(Tab1)))>
              (se("Item 1"))
            </Nav.Link>
          </Nav.Item>
          <Nav.Item>
            <Nav.Link
              active=(state.activeTab == Tab2)
              onClick=(_event => dispatch(SwitchTab(Tab2)))>
              (se("Item 2"))
            </Nav.Link>
          </Nav.Item>
        </Nav>
        <Tab.Content active=state.activeTab> ...panels </Tab.Content>
      </div>
      (Examples.highlight(code))
    </Examples.Example>;
  };


