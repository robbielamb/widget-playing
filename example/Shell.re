type state = {currentRoute: Routes.t};

type action =
  | SetRoute(Routes.t)
  | Open
  | Close;

let navTo = (route, event, _self) => {
  ReactEvent.Mouse.preventDefault(event);
  Navigate.to_(route);
};

let navNav = (handle, currentRoute, routeTo, name) => {
  let href = Navigate.pathFor(routeTo);
  let disabled = currentRoute === routeTo;
  let navTo = navTo(routeTo);
  let el =
    <Bootstrap.Nav.Link href disabled onClick=(handle(navTo))>
      (React.string(name))
    </Bootstrap.Nav.Link>;
  el;
};

let component = ReasonReact.reducerComponent("Shell");

let make = _children => {
  ...component,
  initialState: () => {
    currentRoute:
      ReasonReact.Router.dangerouslyGetInitialUrl() |> Router.urlHandler,
  },
  didMount: self => {
    let watcherId =
      ReasonReact.Router.watchUrl(url => {
        let route = Router.urlHandler(url);
        self.send(SetRoute(route));
      });
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherId));
  },
  reducer: (action, _state) =>
    switch (action) {
    | SetRoute(route) => ReasonReact.Update({currentRoute: route})
    | _ => ReasonReact.NoUpdate
    },
  render:
    (self: ReasonReact.self(state, ReasonReact.noRetainedProps, action)) => {
    let element = Router.elementForRoute(self.state.currentRoute);
    let navTo = navNav(self.handle, self.state.currentRoute);
    <div>
      <Bootstrap.Navbar light=false color=Bootstrap.Colors.Background.Dark>
        <Bootstrap.Navbar.Brand>
          (React.string("Widget Play"))
        </Bootstrap.Navbar.Brand>
      </Bootstrap.Navbar>
      <Bootstrap.Layout.Container>
        <Bootstrap.Layout.Row>
          <Bootstrap.Layout.Col> element </Bootstrap.Layout.Col>
          <Bootstrap.Layout.Col
            md=(
              Bootstrap.Layout.Col.shape(
                ~size=Bootstrap.Layout.ColSizes.Size(2),
                (),
              )
            )>
            <p> (React.string("Select Example")) </p>
            <Bootstrap.Nav vertical=true>
              <Bootstrap.Nav.Item>
                (navTo(Routes.AlertExampleRoute, "Alerts"))
                (navTo(Routes.BadgesExampleRoute, "Badges"))
                (navTo(Routes.BreadcrumbExampleRoute, "Breadcrumbs"))
                (navTo(Routes.ButtonExampleRoute, "Buttons"))
                (navTo(Routes.CollapseExampleRoute, "Collapse"))
                (navTo(Routes.DropdownExampleRoute, "Dropdown"))
                (navTo(Routes.FormExampleRoute, "Forms"))
                (navTo(Routes.ModalExampleRoute, "Modals"))
                (navTo(Routes.PaginationExampleRoute, "Pagination"))
                (navTo(Routes.ProgressExampleRoute, "Progress Bars"))
                (navTo(Routes.TableExampleRoute, "Tables"))
                (navTo(Routes.TabExampleRoute, "Tabs"))
              </Bootstrap.Nav.Item>
            </Bootstrap.Nav>
          </Bootstrap.Layout.Col>
        </Bootstrap.Layout.Row>
      </Bootstrap.Layout.Container>
    </div>;
  },
};
/**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
let make =
  ReasonReactCompat.wrapReasonReactForReact(
    ~component, (reactProps: {. "children": 'children}) =>
    make(reactProps##children)
  );
[@bs.obj]
external makeProps: (~children: 'children, unit) => {. "children": 'children} =
  "";
