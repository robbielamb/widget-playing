include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/TabsExample.re')|}] |> Examples.prepCode;

let se = ReasonReact.string;

type tabs =
  | Tab1
  | Tab2;
type state = {activeTab: tabs};
type action =
  | SwitchTab(tabs);
let component = ReasonReact.reducerComponent("TabsExample");
let make = _children => {
  ...component,
  initialState: () => {activeTab: Tab1},
  reducer: (action, _state) =>
    switch (action) {
    | SwitchTab(newTab) => ReasonReact.Update({activeTab: newTab})
    },
  render: ({state, send}) => {
    let panels = [|
      Tab.Pane.create(~tabId=Tab1, se("Something here")),
      Tab.Pane.create(~tabId=Tab2, se("Something else")),
    |];
    <Examples.Example title="Tabs Example">
      <div>
        <Nav tabs=true>
          <Nav.Item>
            <Nav.Link
              active=(state.activeTab == Tab1)
              onClick=(_event => send(SwitchTab(Tab1)))>
              (se("Item 1"))
            </Nav.Link>
          </Nav.Item>
          <Nav.Item>
            <Nav.Link
              active=(state.activeTab == Tab2)
              onClick=(_event => send(SwitchTab(Tab2)))>
              (se("Item 2"))
            </Nav.Link>
          </Nav.Item>
        </Nav>
        <Tab.Content active=state.activeTab> ...panels </Tab.Content>
      </div>
      (Examples.highlight(code))
    </Examples.Example>;
  },
};
